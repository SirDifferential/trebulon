#ifndef __PLAYER_HPP_
#define __PLAYER_HPP_

#include <SFML/Graphics.hpp>
#include <memory>

class Player
{
private:
    std::shared_ptr<sf::Sprite> sprite;
public:
    Player();
    ~Player();

    void render();
    void update();
    void setPosition(int x, int y);
};

#endif
