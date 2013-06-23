#include "probe.hpp"
#include "game.hpp"
#include "datastorage.hpp"
#include "water.hpp"

Probe::Probe(sf::Vector2f coords)
{
    sprite = game.getDataStorage()->getSprite("probe");
    burrowedSprite = game.getDataStorage()->getSprite("probe_burrowed");
    position = coords;
    radius = 300.0f;
    installTime = game.getTime();
    spriteChangeTime = installTime + 60.0;
    scale = 1.5;
    scalePerTick = 0.5/60;
}

Probe::~Probe()
{
}

void Probe::update()
{
    if (game.getTime() < spriteChangeTime)
    {
        scale -= scalePerTick;
        sprite->setRotation(scale*10);
        sprite->setScale(scale, scale);
    }
    if (game.getTime() > spriteChangeTime)
    {
        sprite->setScale(1, 1);
        sprite = burrowedSprite;
    }
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
