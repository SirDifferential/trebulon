#ifndef __WATER_HPP_
#define __WATER_HPP_

#include <SFML/Graphics.hpp>

class Water
{
private:
    sf::Vector2f position;
    float depth;
    float deposit_size;
public:
    Water();
    ~Water();

    void setPosition(sf::Vector2f v);
    sf::Vector2f getPosition();
    void setDepth(float d);
    float getDepth();
    void setSize(float s);
    float getSize();
    long giveWater(long rate);

};

#endif
