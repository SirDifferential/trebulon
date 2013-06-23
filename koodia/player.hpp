#ifndef __PLAYER_HPP_
#define __PLAYER_HPP_

#include <SFML/Graphics.hpp>
#include <memory>

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

    int drillsLeft;
    int probesLeft;
    long objectPlantTime;
    long nextPlantTime;
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
};

#endif
