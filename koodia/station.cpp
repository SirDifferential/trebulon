#include "station.hpp"
#include "game.hpp"
#include "datastorage.hpp"

Station::Station(sf::Vector2f coords)
{
    position = coords;
    sprite = game.getDataStorage()->getSprite("station");
}

Station::~Station()
{
}

void Station::update()
{
}

void Station::render()
{
    sprite->setPosition(position.x, position.y);
    game.getRenderWindow()->draw((*sprite));
}
