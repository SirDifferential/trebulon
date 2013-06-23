#include "world.hpp"
#include "game.hpp"
#include "textRenderer.hpp"
#include "toolbox.hpp"
#include <noise/noise.h>
#include "noiseutils.h"

#include <memory>
#include <thread>
#include <mutex>

using namespace noise;

std::mutex dataMutex;

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
void storeWorldCreationResult(World* w, std::shared_ptr<sf::Sprite> sprite, std::shared_ptr<sf::Texture> texture, std::pair<int,int> coords)
{
    dataMutex.lock();
    w->worldMapData[coords] = texture;
    w->worldMap[coords] = sprite;
    w->activeMapRegions.push_back(w->worldMap[coords]);
    dataMutex.unlock();
}

void createWorldRegion(World* world, std::vector<int>& params)
{
    if (params.size() < 6)
    {
        fprintf(stderr, "! World: Error at multithread world creation! Params size was %d when 6 was expected!\n", params.size());
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
    int size_x = params.at(4);
    int size_y = params.at(5);

    std::pair<int,int> tempPair;
    tempPair.first = x_start;   // TODO: Verify
    tempPair.second = y_start;

    module::Perlin myModule;
    utils::NoiseMap heightMap;
    utils::NoiseMapBuilderPlane heightMapBuilder;
    heightMapBuilder.SetSourceModule (myModule);
    heightMapBuilder.SetDestNoiseMap (heightMap);
    heightMapBuilder.SetDestSize (size_x, size_y);
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

    tempTexture->create(size_x, size_y);
    tempTexture->update((*tempImage));
    //world->worldMapData[tempPair] = tempTexture;
    tempSprite->setTexture((*tempTexture));
    tempSprite->setPosition(x_start*32, y_start*32);
    //world->worldMap[tempPair] = tempSprite;
    //world->activeMapRegions.push_back(world->worldMap[tempPair]);

    storeWorldCreationResult(world, tempSprite, tempTexture, tempPair);

    fprintf(stderr, "# World: creation finished\n");
}

void dummy(std::vector<int>& params)
{
}

void World::createWorld()
{
    int x_start = 0;
    int y_start = 0;
    int x_end = 0;
    int y_end = 0;
    int regionSize = 512;

    // Uh, why doesn't std::thread accept over 5 parameters? A temporary fix, for now...
    //int numberOfThreads = 8;
    int regionsToCreate = 12;
    std::vector<std::shared_ptr<std::thread>> threadContainer;
    std::vector<int> params;
    params.push_back(x_start);
    params.push_back(x_end);
    params.push_back(y_start);
    params.push_back(y_end);
    params.push_back(regionSize);
    params.push_back(regionSize);
    std::vector<int>& paramsRef = params;


    game.getRenderWindow()->clear();
    std::string temp = game.getToolbox()->createString("Creating world! Please wait warmly...\nChunks finished: ", 0, " out of ", 81);
    game.getTextRenderer()->renderText(20, 20, temp, FONT_SIZE::LARGE_FONT, true, sf::Color::Magenta);
    game.forceRedraw();

    for (int y = -64; y < 65; y += 16)
    {
        for (int x = -64; x < 65; x += 16)
        {
            params.at(0) = x;
            params.at(1) = x + 16;
            params.at(2) = y;
            params.at(3) = y + 16;
            params.at(4) = 512;
            params.at(5) = 512;
            std::shared_ptr<std::thread> temp = std::shared_ptr<std::thread>(new std::thread(createWorldRegion, this, paramsRef));
            threadContainer.push_back(temp);
            fprintf(stderr, "# World: Created thread number %d\n", threadContainer.size());
        }
    }

    fprintf(stderr, "# World: Waiting for %d threads to exit\n", threadContainer.size());
    int count = 1;
    for (auto iter = threadContainer.begin(); iter != threadContainer.end(); iter++)
    {
        game.getRenderWindow()->clear();
        std::string temp = game.getToolbox()->createString("Creating world! Please wait warmly...\nChunks finished: ", count, " out of ", threadContainer.size());
        game.getTextRenderer()->renderText(20, 20, temp, FONT_SIZE::LARGE_FONT, true, sf::Color::Magenta);
        game.forceRedraw();
        
        (*iter)->join();
        fprintf(stderr, "%d / %d threads finished\n", count, threadContainer.size());
        count++;
    }

    threadContainer.clear();
}

void World::render()
{
    for (auto iter = activeMapRegions.begin(); iter != activeMapRegions.end(); iter++)
    {
        game.getRenderWindow()->draw((*iter->get()));
    }
}

void World::update()
{
}
