#ifndef __TOOLBOX_HPP_
#define __TOOLBOX_HPP_

#include <string>
#include <SFML/Graphics.hpp>

class Toolbox
{
private:
public:
    Toolbox();
    ~Toolbox();

    std::string createString(std::string s, float i);
    std::string createString(std::string s1, float num1, std::string s2, float num2);
    int giveRandomInt(int min, int max);
    float vectorDistance(sf::Vector2f a, sf::Vector2f b);
};

#endif
