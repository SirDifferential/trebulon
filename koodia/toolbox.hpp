#ifndef __TOOLBOX_HPP_
#define __TOOLBOX_HPP_

#include <string>

class Toolbox
{
private:
public:
    Toolbox();
    ~Toolbox();

    std::string createString(std::string s, float i);
    std::string createString(std::string s1, float num1, std::string s2, float num2);
};

#endif
