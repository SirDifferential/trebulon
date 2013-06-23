#include "world.hpp"
#include "game.hpp"
#include "textRenderer.hpp"
#include "toolbox.hpp"
#include "player.hpp"
#include "units.hpp"
#include <noise/noise.h>
#include "noiseutils.h"

#include <memory>
#include <thread>
#include <mutex>
#include <chrono>

using namespace noise;

std::mutex dataMutex;
std::vector<std::shared_ptr<std::thread>> threadContainer;
std::mutex updateMutex;
std::mutex threadReady;
int threads_in_use = 0;
const int max_threads = 8;
int threads_reported_ready = 0;

World::World()
{
}

World::~World()
{
}


/**
* Thread safe function for storing the result of world creation
* in the data containers of the World class
* Takes the world creation sprite and its data (texture) as params,
* as well as the coordinates where it shoudl exist
*/
void storeWorldCreationResult(std::shared_ptr<World> w, std::shared_ptr<sf::Sprite> sprite, std::shared_ptr<sf::Texture> texture, std::pair<int,int> coords)
{
    dataMutex.lock();
    w->worldMapData[coords] = texture;
    w->worldMap[coords] = sprite;
    w->activeMapRegions.push_back(w->worldMap[coords]);
    dataMutex.unlock();
}

void updateThreadUsage(bool plus)
{
    updateMutex.lock();
    if (plus)
        threads_in_use++;
    else
        threads_in_use--;
    updateMutex.unlock();
}

void incrementThreadReadiness()
{
    threadReady.lock();
    threads_reported_ready++;
    threadReady.unlock();
}

int getThreadUsage()
{
    updateMutex.lock();
    int out = threads_in_use;
    updateMutex.unlock();
    return out;
}

int getThreadsReady()
{
    threadReady.lock();
    int out = threads_reported_ready;
    threadReady.unlock();
    return out;
}

void createWorldRegion(std::shared_ptr<World> world, std::vector<int>& params)
{
    if (params.size() < 4)
    {
        fprintf(stderr, "! World: Error at multithread world creation! Params size was %d when 4 was expected!\n", params.size());
        fprintf(stderr, "! World: The params were:\n");
        for (auto iter = params.begin(); iter != params.end(); iter++)
        {
            fprintf(stderr, "! World: %d ", (*iter));
        }
        fprintf(stderr, "\n");
        return;
    }
    int x_start = params.at(0);
    int x_end = params.at(1);
    int y_start = params.at(2);
    int y_end = params.at(3);
    //int size_x = params.at(4);
    //int size_y = params.at(5);

    std::pair<int,int> tempPair;
    tempPair.first = x_start;
    tempPair.second = y_start;

    module::Perlin myModule;
    utils::NoiseMap heightMap;
    utils::NoiseMapBuilderPlane heightMapBuilder;
    heightMapBuilder.SetSourceModule (myModule);
    heightMapBuilder.SetDestNoiseMap (heightMap);
    heightMapBuilder.SetDestSize (REGION_SIZE, REGION_SIZE);
    heightMapBuilder.SetBounds (x_start, x_end, y_start, y_end);
    heightMapBuilder.Build ();

    utils::RendererImage renderer;
    utils::Image image;
    renderer.SetSourceNoiseMap (heightMap);
    renderer.SetDestImage (image);
    renderer.ClearGradient ();
    renderer.AddGradientPoint (-1.00, utils::Color ( 32, 160,   0, 255)); // grass
    renderer.AddGradientPoint (-0.25, utils::Color (224, 224,   0, 255)); // dirt
    renderer.AddGradientPoint ( 0.25, utils::Color (128, 128, 128, 255)); // rock
    renderer.AddGradientPoint ( 1.00, utils::Color (255, 255, 255, 255)); // snow
    renderer.EnableLight ();
    renderer.SetLightContrast (3.0);
    renderer.SetLightBrightness (2.0);
    renderer.Render ();
    
    std::shared_ptr<sf::Sprite> tempSprite(new sf::Sprite());
    std::shared_ptr<sf::Texture> tempTexture(new sf::Texture());
    std::shared_ptr<sf::Image> tempImage = std::shared_ptr<sf::Image>(new sf::Image());
    tempImage->create(image.GetWidth(), image.GetHeight());

    utils::Color c;

    fprintf(stderr, "# World: Copying world data to sf::sprite\n");
    for (int i = 0; i < image.GetWidth(); i++)
    {
        for (int j = 0; j < image.GetHeight(); j++)
        {
            c = image.GetValue(i,j);
            tempImage->setPixel(i, j, sf::Color(c.red, c.green, c.red, c.alpha));
        }
    }

    tempTexture->create(REGION_SIZE, REGION_SIZE);
    tempTexture->update((*tempImage));
    //world->worldMapData[tempPair] = tempTexture;
    tempSprite->setTexture((*tempTexture));
    tempSprite->setPosition(x_start*REGION_SIZE/NOISE_SIZE, y_start*REGION_SIZE/NOISE_SIZE);
    //world->worldMap[tempPair] = tempSprite;
    //world->activeMapRegions.push_back(world->worldMap[tempPair]);

    storeWorldCreationResult(world, tempSprite, tempTexture, tempPair);

    updateThreadUsage(false);
    incrementThreadReadiness();
    fprintf(stderr, "# World: creation finished\n");
}

void World::createWorld()
{
    int x_start = 0;
    int y_start = 0;
    int x_end = 0;
    int y_end = 0;
    //int regionSize = 512;

    // Uh, why doesn't std::thread accept over 5 parameters? A temporary fix, for now...
    //int numberOfThreads = 8;
    //int regionsToCreate = 12;
    std::vector<int>& params = std::vector<int>();
    params.push_back(x_start);
    params.push_back(x_end);
    params.push_back(y_start);
    params.push_back(y_end);
    //params.push_back(REGION_SIZE);
    //params.push_back(REGION_SIZE);

    game.getRenderWindow()->clear();
    std::string temp = game.getToolbox()->createString("Creating world! Please wait warmly...\nChunks finished: ", 0, " out of ", (INITIAL_AREA/NOISE_SIZE*2)*(INITIAL_AREA/NOISE_SIZE*2));
    game.getTextRenderer()->renderText(20, 20, temp, FONT_SIZE::LARGE_FONT, true, sf::Color::Magenta);
    game.forceRedraw();

    for (int y = -INITIAL_AREA; y <= INITIAL_AREA; y += NOISE_SIZE)
    {
        for (int x = -INITIAL_AREA; x <= INITIAL_AREA; x += NOISE_SIZE)
        {
            params.at(0) = x;
            params.at(1) = x + NOISE_SIZE;
            params.at(2) = y;
            params.at(3) = y + NOISE_SIZE;

            // Limit thread spam
            while (getThreadUsage() >= max_threads)
            {
                std::this_thread::sleep_for(std::chrono::microseconds(10));
            }

            std::shared_ptr<std::thread> temp = std::shared_ptr<std::thread>(new std::thread(createWorldRegion, game.getWorld(), params));
            updateThreadUsage(true);
            threadContainer.push_back(temp);
            fprintf(stderr, "# World: Created thread number %d\n", threadContainer.size());

            game.getRenderWindow()->clear();
            std::string tempText = game.getToolbox()->createString("Creating world! Please wait warmly...\nChunks finished: ", getThreadsReady(), " out of ", (INITIAL_AREA*2/NOISE_SIZE)*(INITIAL_AREA*2/NOISE_SIZE));
            game.getTextRenderer()->renderText(20, 20, tempText, FONT_SIZE::LARGE_FONT, true, sf::Color::Magenta);
            game.forceRedraw();
        }
    }

    fprintf(stderr, "# World: Waiting for %d threads to exit\n", threadContainer.size());
    int count = 1;
    for (auto iter = threadContainer.begin(); iter != threadContainer.end(); iter++)
    {
        game.getRenderWindow()->clear();
        std::string temp = game.getToolbox()->createString("Creating world! Please wait warmly...\nChunks finished: ", count, " out of ", (INITIAL_AREA*2/NOISE_SIZE)*(INITIAL_AREA*2/NOISE_SIZE));
        game.getTextRenderer()->renderText(20, 20, temp, FONT_SIZE::LARGE_FONT, true, sf::Color::Magenta);
        game.forceRedraw();
        fprintf(stderr, "%d / %d threads finished\n", count, threadContainer.size());
        (*iter)->join();
        count++;
    }

    threadContainer.clear();

    /*
    for (int y = -INITIAL_AREA; y <= INITIAL_AREA; y += NOISE_SIZE)
    {
        for (int x = -INITIAL_AREA; x <= INITIAL_AREA; x += NOISE_SIZE)
        {
            params.at(0) = x;
            params.at(1) = x + NOISE_SIZE;
            params.at(2) = y;
            params.at(3) = y + NOISE_SIZE;
            //params.at(4) = REGION_SIZE;
            //params.at(5) = REGION_SIZE;
            std::shared_ptr<std::thread> temp = std::shared_ptr<std::thread>(new std::thread(createWorldRegion, game.getWorld(), paramsRef));
            threadContainer.push_back(temp);
            fprintf(stderr, "# World: Created thread number %d\n", threadContainer.size());
        }
    }
    */

    fprintf(stderr, "# World: Waiting for %d threads to exit\n", threadContainer.size());
    count = 1;
    for (auto iter = threadContainer.begin(); iter != threadContainer.end(); iter++)
    {
        game.getRenderWindow()->clear();
        std::string temp = game.getToolbox()->createString("Creating world! Please wait warmly...\nChunks finished: ", count, " out of ", (INITIAL_AREA*2/NOISE_SIZE)*(INITIAL_AREA*2/NOISE_SIZE));
        game.getTextRenderer()->renderText(20, 20, temp, FONT_SIZE::LARGE_FONT, true, sf::Color::Magenta);
        game.forceRedraw();
        fprintf(stderr, "%d / %d threads finished\n", count, threadContainer.size());
        (*iter)->join();
        count++;
    }

    
}

void World::render()
{
    for (auto iter = activeMapRegions.begin(); iter != activeMapRegions.end(); iter++)
    {
        game.getRenderWindow()->draw((*iter->get()));
    }
}

std::shared_ptr<sf::Sprite> World::checkRegionAtCoords(std::pair<int,int> coords)
{
    std::map<std::pair<int,int>, std::shared_ptr<sf::Sprite>>::iterator iter = worldMap.find(coords);
    if (iter != worldMap.end())
        return iter->second;
    else
    {
        return nullptr;
    }
}

void World::update()
{
    // See if new areas need to be generated
    std::pair<int,int> playerRegion = game.getPlayer()->getRegion();
    std::pair<int,int> searchRegion = playerRegion;
    std::vector<int>& params = std::vector<int>();
/*
    // Search an area of 4 units in all directions
    // If no existing land was found, generate it
    for (int y = playerRegion.second - 4*NOISE_SIZE; y < playerRegion.second + 4*NOISE_SIZE; y += NOISE_SIZE)
    {
        for (int x = playerRegion.first - 4*NOISE_SIZE; x < playerRegion.first + 4*NOISE_SIZE; x += NOISE_SIZE)
        {
            searchRegion.first = x;
            searchRegion.second = y;
            params.clear();
            if (checkRegionAtCoords(searchRegion) == nullptr)
            {
                fprintf(stderr, "No terrain found at %d %d\n", searchRegion.first, searchRegion.second);
                params.push_back(searchRegion.first);
                params.push_back(searchRegion.first + NOISE_SIZE);
                params.push_back(searchRegion.second);
                params.push_back(searchRegion.second + NOISE_SIZE);
                createWorldRegion(game.getWorld(), params);
            }
        }
    }
*/
}
