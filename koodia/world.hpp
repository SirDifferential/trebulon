#ifndef __WORLD_HPP_
#define __WORLD_HPP_

#include <memory>
#include <SFML/Graphics.hpp>
#include <map>

class World
{
private:
    std::map<std::pair<int,int>, std::shared_ptr<sf::Sprite>> worldMap;
    std::map<std::pair<int,int>, std::shared_ptr<sf::Texture>> worldMapData;
    std::vector<std::shared_ptr<sf::Sprite>> activeMapRegions;
public:
    World();
    ~World();

    void createWorld(int x_start, int x_end, int y_start, int y_end, int size_x, int size_y);
    void createWorldRegion(int x_start, int x_end, int y_start, int y_end, int size_x=1024, int size_y=1024);
    void render();
};

#endif
