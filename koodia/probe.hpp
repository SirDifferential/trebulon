#ifndef __PROBE_HPP_
#define __PROBE_HPP_

#include <SFML/Graphics.hpp>
#include <memory>

class Probe
{
private:
    sf::Vector2f position;
    std::shared_ptr<sf::Sprite> sprite;
public:
    Probe(sf::Vector2f coords);
    ~Probe();

    void update();
    void render();
};

#endif
