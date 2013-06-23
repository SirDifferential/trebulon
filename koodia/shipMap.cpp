#include "shipMap.hpp"
#include "game.hpp"
#include <algorithm>

ShipMap::ShipMap()
{
}

ShipMap::~ShipMap()
{
}

void ShipMap::update()
{
}

void ShipMap::render()
{
    game.getRenderWindow()->draw((*map));
}

void ShipMap::addDrill(int x, int y)
{
    std::pair<int,int> temp;
    temp.first = x;
    temp.second = y;
    if (std::find(drills.begin(), drills.end(), temp) == drills.end())
        drills.push_back(temp);
}

void ShipMap::addProbe(int x, int y)
{
    std::pair<int,int> temp;
    temp.first = x;
    temp.second = y;
    if (std::find(probes.begin(), probes.end(), temp) == probes.end())
        drills.push_back(temp);
}

void ShipMap::addWater(int x, int y)
{
    std::pair<int,int> temp;
    temp.first = x;
    temp.second = y;
    if (std::find(water.begin(), water.end(), temp) == water.end())
        drills.push_back(temp);
}

void ShipMap::setSprite(std::shared_ptr<sf::Sprite> s)
{
    map = s;
}
