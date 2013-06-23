#ifndef __DRILL_HPP_
#define __DRILL_HPP_

#include <SFML/Graphics.hpp>
#include <memory>

class Water;

class Drill
{
private:
    sf::Vector2f position;
    std::shared_ptr<sf::Sprite> sprite;
    
    long installTime;
    long waterHarvested;
    long transferRate;
    std::shared_ptr<Water> waterDeposit;
    float radius;

public:
    Drill(sf::Vector2f coords);
    ~Drill();

    void update();
    void render();

    long getInstallTime();
    long getWaterHarvested();
    long transferWater();

    void setWater(std::shared_ptr<Water> w);
    float getRadius();
};

#endif
