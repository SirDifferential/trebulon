#ifndef __STATION_HPP_
#define __STATION_HPP_

#include <SFML/Graphics.hpp>
#include <memory>

class Station
{
private:
    sf::Vector2f position;
    std::shared_ptr<sf::Sprite> sprite;
public:
    Station(sf::Vector2f coords);
    ~Station();

    void update();
    void render();
};

#endif
