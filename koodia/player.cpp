#include "player.hpp"
#include "game.hpp"
#include "datastorage.hpp"
#include "textRenderer.hpp"
#include "toolbox.hpp"
#include "units.hpp"
#include "world.hpp"
#include "probe.hpp"
#include "drill.hpp"
#include "shipMap.hpp"
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
    drillsLeft = 5;
    probesLeft = 50;
    objectPlantTime = 0;
    nextPlantTime = 0;
    ui = game.getDataStorage()->getSprite("UI");
    GUI_render_x = -480;
    GUI_render_y = -475;
    mapVisible = false;
}

Player::~Player()
{
}

void Player::render()
{
    ui->setPosition(position.x + GUI_render_x, position.y + GUI_render_y);
    game.getRenderWindow()->draw((*ui));

    std::string speedMeter = game.getToolbox()->createString("Speed: ", speed);
    game.getTextRenderer()->renderText(position.x + GUI_render_x + 10, position.y + GUI_render_y + 20, speedMeter, FONT_SIZE::MEDIUM_FONT, true, sf::Color::White);
    //speedMeter = game.getToolbox()->createString("Set speed: ", desiredSpeed);
    //game.getTextRenderer()->renderText(position.x+30, position.y-120, speedMeter, FONT_SIZE::LARGE_FONT, false, sf::Color::Red);
    game.getRenderWindow()->draw((*sprite));
    std::string regionText = game.getToolbox()->createString("Region X:", playerRegion.first, " Y: ", playerRegion.second);
    game.getTextRenderer()->renderText(position.x + GUI_render_x + 10, position.y + GUI_render_y + 50, regionText, FONT_SIZE::MEDIUM_FONT, true, sf::Color::White);

    //std::string positionText = game.getToolbox()->createString("Pos X", position.x, " Y: ", position.y);
    //game.getTextRenderer()->renderText(position.x + GUI_render_x + 10, position.y + GUI_render_y + 60, positionText, FONT_SIZE::MEDIUM_FONT, true, sf::Color::Red);

    std::string probesLeftStr = game.getToolbox()->createString("Probes: ", probesLeft);
    std::string drillsLeftStr = game.getToolbox()->createString("Drills: ", drillsLeft);
    if (probesLeft <= 0)
        game.getTextRenderer()->renderText(position.x + GUI_render_x + 10, position.y + GUI_render_y + 80, probesLeftStr, FONT_SIZE::MEDIUM_FONT, true, sf::Color::Red);
    else
        game.getTextRenderer()->renderText(position.x + GUI_render_x + 10, position.y + GUI_render_y + 80, probesLeftStr, FONT_SIZE::MEDIUM_FONT, true, sf::Color::Green);

    if (drillsLeft <= 0)
        game.getTextRenderer()->renderText(position.x + GUI_render_x + 10, position.y + GUI_render_y + 110, drillsLeftStr, FONT_SIZE::MEDIUM_FONT, true, sf::Color::Red);
    else
        game.getTextRenderer()->renderText(position.x + GUI_render_x + 10, position.y + GUI_render_y + 110, drillsLeftStr, FONT_SIZE::MEDIUM_FONT, true, sf::Color::Green);

    if (mapVisible && map != nullptr)
    {
        map->render();
    }
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

    if (map != nullptr)
        map->update();
}

void Player::showMap()
{
    if (mapVisible == false)
        mapVisible = true;
    else
        mapVisible = false;
}

void Player::dropDrill()
{
    if (drillsLeft <= 0)
    {
        fprintf(stderr, "# Player: no drills left!\n");
        return;
    }
    if (nextPlantTime > game.getTime())
    {
        fprintf(stderr, "# Player: Can't place drills yet! %d %d %d\n", game.getTime(), objectPlantTime, nextPlantTime);
        return;
    }
    game.getWorld()->addDrill(position);
    objectPlantTime = game.getTime();
    nextPlantTime = objectPlantTime + 200;
    drillsLeft--;
}

void Player::dropProbe()
{
    if (probesLeft <= 0)
    {
        fprintf(stderr, "# Player: no probes left!\n");
        return;
    }
    if (nextPlantTime > game.getTime())
    {
        fprintf(stderr, "# Player: Can't place probes yet! %d %d %d\n", game.getTime(), objectPlantTime, nextPlantTime);
        return;
    }
    game.getWorld()->addProbe(position);
    objectPlantTime = game.getTime();
    nextPlantTime = objectPlantTime + 200;
    probesLeft--;
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

void Player::addMap(std::shared_ptr<ShipMap> m)
{
    map = m;
}
