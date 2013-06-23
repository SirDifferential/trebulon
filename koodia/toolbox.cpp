#include "toolbox.hpp"
#include <sstream>

Toolbox::Toolbox()
{
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
