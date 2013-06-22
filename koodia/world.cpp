#include "world.hpp"
#include "game.hpp"
#include "textRenderer.hpp"
#include <noise/noise.h>
#include "noiseutils.h"

using namespace noise;

World::World()
{
}

World::~World()
{
}

void World::createWorldRegion(int x_start, int x_end, int y_start, int y_end, int size_x, int size_y)
{
}

void World::createWorld(int x_start, int x_end, int y_start, int y_end, int size_x, int size_y)
{

    std::pair<int,int> tempPair;
    tempPair.first = x_start;   // TODO: Verify
    tempPair.second = y_start;

    // Generate many areas using threads

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
    worldMapData[tempPair] = tempTexture;
    tempSprite->setTexture((*tempTexture));
    tempSprite->setPosition(x_start*32, y_start*32);
    worldMap[tempPair] = tempSprite;
    activeMapRegions.push_back(worldMap[tempPair]);
    fprintf(stderr, "# World: creation finished\n");
}

void World::render()
{
    for (auto iter = activeMapRegions.begin(); iter != activeMapRegions.end(); iter++)
    {
        game.getRenderWindow()->draw((*iter->get()));
    }
}
