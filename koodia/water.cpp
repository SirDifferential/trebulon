#include "water.hpp"

Water::Water()
{
}

Water::~Water()
{
}

void Water::setPosition(sf::Vector2f v)
{
    position = v;
}

sf::Vector2f Water::getPosition()
{
    return position;
}

void Water::setDepth(float d)
{
    depth = d;
}

float Water::getDepth()
{
    return depth;
}

void Water::setSize(float s)
{
    deposit_size = s;
}

float Water::getSize()
{
    return deposit_size;
}

long Water::giveWater(long rate)
{
    if (deposit_size > rate)
    {
        deposit_size -= rate;
        return rate;
    }
    else
    {
        long out = deposit_size;
        deposit_size = 0;
        return out;
    }
}
