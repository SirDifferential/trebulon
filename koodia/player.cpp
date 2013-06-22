#include "player.hpp"
#include "game.hpp"
#include "datastorage.hpp"

Player::Player()
{
    sf::IntRect subRect;
    subRect.left = 0;
    subRect.top = 0;
    subRect.width = 64;
    subRect.height = 64;
    std::shared_ptr<sf::Texture> texturePointer = game.getDataStorage()->getTexture("player");
    if (texturePointer == nullptr)
    {
        fprintf(stderr, "! Player: Cannot create texture. Desired texture not found in memory: player\n");
    }
    sprite = std::shared_ptr<sf::Sprite>(new sf::Sprite((*texturePointer), subRect));
    sprite->setOrigin(sf::Vector2f(32,32));

    desiredSpeed = 0;
    speed = 0;
    position = sf::Vector2f(400, 300);
    velocity = sf::Vector2f(1,1);
    acceleration = sf::Vector2f(1.0, 1.0);
    facing = 180;
    rotationalSpeed = 2.0f;
}

Player::~Player()
{
}

void Player::render()
{
    game.getRenderWindow()->draw((*sprite));
}

void Player::update()
{
    speed = sqrt((velocity.x * velocity.x) + (velocity.y * velocity.y));
    if (speed - desiredSpeed < -0.11)
    {
        velocity.x += cos((double)facing*3.14159/180.0)*acceleration.x;
        velocity.y += sin((double)facing*3.14159/180.0)*acceleration.y;
    }
    else if (speed - desiredSpeed > 0.11)
    {
        velocity.x -= cos((double)facing*3.14159/180.0)*acceleration.x;
        velocity.y -= sin((double)facing*3.14159/180.0)*acceleration.y;
    }
    position.x += cos((double)facing*3.14159/180.0)*velocity.x;
    position.y += sin((double)facing*3.14159/180.0)*velocity.y;
    sprite->setPosition(position.x, position.y);
    sprite->setRotation(facing);
}

void Player::setPosition(int x, int y)
{
    position = sf::Vector2f(x,y);
    sprite->setPosition(position.x, position.y);
}

void Player::setSpeed(float s)
{
    speed = s;
}

/**
* After the player gives a desired speed, this function sees
* if that speed can be reached
*/
void Player::setDesiredSpeed(float s)
{
    desiredSpeed = s;
}

void Player::rotateLeft()
{
    facing -= rotationalSpeed;
    if (facing < 0)
        facing = 360;
}

void Player::rotateRight()
{
    facing += rotationalSpeed;
    if (facing > 360)
        facing = 0;
}
