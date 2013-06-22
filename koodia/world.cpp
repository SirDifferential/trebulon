#include "world.hpp"
#include "game.hpp"
#include <noise/noise.h>
#include "noiseutils.h"

using namespace noise;

World::World()
{
    worldMap = nullptr;
}

World::~World()
{
}

void World::createWorld()
{
    module::RidgedMulti mountainTerrain;

    module::Billow baseFlatTerrain;
    baseFlatTerrain.SetFrequency (2.0);

    module::ScaleBias flatTerrain;
    flatTerrain.SetSourceModule (0, baseFlatTerrain);
    flatTerrain.SetScale (0.125);
    flatTerrain.SetBias (-0.75);

    module::Perlin terrainType;
    terrainType.SetFrequency (0.5);
    terrainType.SetPersistence (0.25);

    module::Select terrainSelector;
    terrainSelector.SetSourceModule (0, flatTerrain);
    terrainSelector.SetSourceModule (1, mountainTerrain);
    terrainSelector.SetControlModule (terrainType);
    terrainSelector.SetBounds (0.0, 1000.0);
    terrainSelector.SetEdgeFalloff (0.125);

    module::Turbulence finalTerrain;
    finalTerrain.SetSourceModule (0, terrainSelector);
    finalTerrain.SetFrequency (4.0);
    finalTerrain.SetPower (0.125);

    utils::NoiseMap heightMap;
    utils::NoiseMapBuilderPlane heightMapBuilder;
    heightMapBuilder.SetSourceModule (finalTerrain);
    heightMapBuilder.SetDestNoiseMap (heightMap);
    heightMapBuilder.SetDestSize (256, 256);
    heightMapBuilder.SetBounds (6.0, 10.0, 1.0, 5.0);
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

    worldMapData = std::shared_ptr<sf::Texture>(new sf::Texture());
    worldMapData->create(image.GetWidth(), image.GetHeight());
    sf::Image tempData;
    tempData.create(image.GetWidth(), image.GetHeight());
    utils::Color c;

    for (int i = 0; i < image.GetWidth(); i++)
    {
        for (int j = 0; j < image.GetHeight(); j++)
        {
            c = image.GetValue(i,j);
            tempData.setPixel(i, j, sf::Color(c.red, c.green, c.red, c.alpha));
        }
    }

    worldMapData->update(tempData);
    worldMap = std::shared_ptr<sf::Sprite>(new sf::Sprite());
    worldMap->setTexture((*worldMapData));
}

void World::render()
{
    game.getRenderWindow()->draw((*worldMap));
}
