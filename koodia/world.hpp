#ifndef __WORLD_HPP_
#define __WORLD_HPP_

#include <memory>
#include <SFML/Graphics.hpp>
#include <map>

class World
{
public:
    std::map<std::pair<int,int>, std::shared_ptr<sf::Sprite>> worldMap;
    std::map<std::pair<int,int>, std::shared_ptr<sf::Texture>> worldMapData;
    std::vector<std::shared_ptr<sf::Sprite>> activeMapRegions;
    int regionCount;
    std::pair<int,int> currentRegion;

    World();
    ~World();

    void createWorld();
    void render();
    void update();

    std::shared_ptr<sf::Sprite> checkRegionAtCoords(std::pair<int,int> coords);
};

#endif
