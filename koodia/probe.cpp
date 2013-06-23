#include "probe.hpp"
#include "game.hpp"
#include "datastorage.hpp"

Probe::Probe(sf::Vector2f coords)
{
    sprite = game.getDataStorage()->getSprite("probe");
    position = coords;
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
