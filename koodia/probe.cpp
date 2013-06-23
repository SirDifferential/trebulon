#include "probe.hpp"
#include "game.hpp"
#include "datastorage.hpp"
#include "water.hpp"

Probe::Probe(sf::Vector2f coords)
{
    sprite = game.getDataStorage()->getSprite("probe");
    position = coords;
    radius = 300.0f;
}

Probe::~Probe()
{
}

void Probe::update()
{
}

void Probe::render()
{
    sprite->setPosition(position.x, position.y);
    game.getRenderWindow()->draw((*sprite));
}

float Probe::getRadius()
{
    return radius;
}

void Probe::setWater(std::shared_ptr<Water> w)
{
    water = w;
}
