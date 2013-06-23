#ifndef __WORLD_HPP_
#define __WORLD_HPP_

#include <memory>
#include <SFML/Graphics.hpp>
#include <map>

class Water;
class Drill;
class Probe;
class Station;

class World
{
public:
    std::map<std::pair<int,int>, std::shared_ptr<sf::Sprite>> worldMap;
    std::map<std::pair<int,int>, std::shared_ptr<sf::Texture>> worldMapData;
    std::vector<std::shared_ptr<sf::Sprite>> activeMapRegions;
    int regionCount;
    std::pair<int,int> currentRegion;
    int waterDepositCount;
    std::vector<std::shared_ptr<Water>> waterDeposits;
    std::vector<std::shared_ptr<Drill>> drills;
    std::vector<std::shared_ptr<Probe>> probes;
    std::shared_ptr<Station> station;

    World();
    ~World();

    void createWorld();
    void render();
    void update();
    void addDrill(sf::Vector2f coords);
    void addProbe(sf::Vector2f coords);

    std::shared_ptr<Water> checkNearbyWater(sf::Vector2f coords, float radius);

    std::shared_ptr<sf::Sprite> checkRegionAtCoords(std::pair<int,int> coords);
};

#endif
