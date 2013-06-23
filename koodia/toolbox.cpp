#include "toolbox.hpp"
#include <sstream>
#include <time.h>

Toolbox::Toolbox()
{
    srand(time(0));
}

Toolbox::~Toolbox()
{
}

std::string Toolbox::createString(std::string s, float i)
{
    std::string out = "";
    std::stringstream ss;
    ss << s;
    ss << i;
    out = ss.str();
    return out;
}

std::string Toolbox::createString(std::string s1, float num1, std::string s2, float num2)
{

    std::string out = "";
    std::stringstream ss;
    ss << s1;
    ss << num1;
    ss << s2;
    ss << num2;
    out = ss.str();
    return out;
}


// Returns a random integer in range (min, max)
int Toolbox::giveRandomInt(int min, int max)
{
    return ((rand()%(max-min))+min);
}

float Toolbox::vectorDistance(sf::Vector2f a, sf::Vector2f b)
{
    return sqrt(abs((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y)));
}
