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
public:
    Player();
    ~Player();

    void render();
    void update();
    void setPosition(int x, int y);

    void setSpeed(float speed);
    void setDesiredSpeed(float speed);

    void rotateLeft();
    void rotateRight();
};

#endif
