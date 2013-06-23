#include "player.hpp"
#include "game.hpp"
#include "datastorage.hpp"
#include "textRenderer.hpp"
#include "toolbox.hpp"
#include "units.hpp"
#include <math.h>

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
    acceleration = sf::Vector2f(0.01, 0.01);
    facing = 180;
    rotationalSpeed = 2.0f;
}

Player::~Player()
{
}

void Player::render()
{
    std::string speedMeter = game.getToolbox()->createString("Speed: ", speed);
    game.getTextRenderer()->renderText(position.x+30, position.y-80, speedMeter, FONT_SIZE::LARGE_FONT, false, sf::Color::Red);
    speedMeter = game.getToolbox()->createString("Set speed: ", desiredSpeed);
    game.getTextRenderer()->renderText(position.x+30, position.y-120, speedMeter, FONT_SIZE::LARGE_FONT, false, sf::Color::Red);
    game.getRenderWindow()->draw((*sprite));
    std::string regionText = game.getToolbox()->createString("Region X:", playerRegion.first, " Y: ", playerRegion.second);
    game.getTextRenderer()->renderText(position.x+30, position.y-40, regionText, FONT_SIZE::LARGE_FONT, true, sf::Color::Red);

    std::string positionText = game.getToolbox()->createString("Pos X", position.x, " Y: ", position.y);
    game.getTextRenderer()->renderText(position.x+30, position.y+80, positionText, FONT_SIZE::LARGE_FONT, true, sf::Color::Red);
}

void Player::update()
{
    speed = sqrt((velocity.x * velocity.x) + (velocity.y * velocity.y));
    if (speed < 0.1)
        speed = 0.0;
    
    if (velocity.x > desiredSpeed)
        velocity.x -= acceleration.x;
    if (velocity.y > desiredSpeed)
        velocity.y -= acceleration.x;
    if (velocity.x < desiredSpeed)
        velocity.x += acceleration.x;
    if (velocity.y < desiredSpeed)
        velocity.y += acceleration.y;
    

    position.x += cos((double)facing*3.14159/180.0)*velocity.x;
    position.y += sin((double)facing*3.14159/180.0)*velocity.y;
    sprite->setPosition(position.x, position.y);
    sprite->setRotation(facing);

    // Gives the largest multiple of REGION_SIZE that the player position contains
    // This is used for figuring out in which region of the world the player currently roves in
    // SFML coordinates use negative Y for up, must be converted
    playerRegion.first = floor(position.x / REGION_SIZE) * NOISE_SIZE;
    playerRegion.second = floor(-position.y / REGION_SIZE) * NOISE_SIZE;
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

sf::Vector2f Player::getPosition()
{
    return position;
}

std::pair<int,int> Player::getRegion()
{
    return playerRegion;
}
