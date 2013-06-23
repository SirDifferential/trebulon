#ifndef __PLAYER_HPP_
#define __PLAYER_HPP_

#include "shipMap.hpp"

#include <SFML/Graphics.hpp>
#include <memory>

class ShipMap;

class Player
{
private:
    std::shared_ptr<sf::Sprite> sprite;
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    float facing;
    float speed;
    float desiredSpeed;
    float rotationalSpeed;
    std::pair<int,int> playerRegion;
    std::shared_ptr<sf::Sprite> ui;
    std::shared_ptr<ShipMap> map;

    int drillsLeft;
    int probesLeft;
    long objectPlantTime;
    long nextPlantTime;
    int GUI_render_x;
    int GUI_render_y;
    bool mapVisible;
public:
    Player();
    ~Player();

    void render();
    void update();
    void setPosition(int x, int y);
    sf::Vector2f getPosition();
    std::pair<int,int> getRegion();

    void setSpeed(float speed);
    void setDesiredSpeed(float speed);

    void rotateLeft();
    void rotateRight();

    void dropDrill();
    void dropProbe();

    void addMap(std::shared_ptr<ShipMap> m);
    void showMap();

};

#endif
