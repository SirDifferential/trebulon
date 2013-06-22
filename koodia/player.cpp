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
    
}

void Player::setPosition(int x, int y)
{
    sprite->setPosition(x, y);
}
