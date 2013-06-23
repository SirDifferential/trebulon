#ifndef __PROBE_HPP_
#define __PROBE_HPP_

#include <SFML/Graphics.hpp>
#include <memory>

class Water;

class Probe
{
private:
    sf::Vector2f position;
    std::shared_ptr<sf::Sprite> sprite;
    float radius;
    std::shared_ptr<Water> water;
public:
    Probe(sf::Vector2f coords);
    ~Probe();

    void update();
    void render();

    float getRadius();
    void setWater(std::shared_ptr<Water> w);
};

#endif
