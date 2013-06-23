#ifndef __SHIPMAP_HPP__
#define __SHIPMAP_HPP__

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

class ShipMap
{
private:
    std::shared_ptr<sf::Sprite> map;
    std::vector<std::pair<int,int>> water;
    std::vector<std::pair<int,int>> drills;
    std::vector<std::pair<int,int>> probes;
public:
    ShipMap();
    ~ShipMap();

    void update();
    void render();

    void addProbe(int x, int y);
    void addDrill(int x, int y);
    void addWater(int x, int y);

    void setSprite(std::shared_ptr<sf::Sprite> s);

};

#endif
