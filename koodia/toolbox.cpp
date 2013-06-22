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
