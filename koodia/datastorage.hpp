#ifndef __DATASTORAGE_HPP_
#define __DATASTORAGE_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>
#include <vector>
#include <memory>
#include <string>

class DataStorage
{
private:
    std::map<std::string, std::shared_ptr<sf::Texture>> textureMap;
    std::vector<std::shared_ptr<sf::Music>> musicVector;
public:
    DataStorage();
    ~DataStorage();

    void loadData();
    int loadTexture(std::string name, std::string path);
    int loadMusic(int id, std::string path);

    std::shared_ptr<sf::Texture> getTexture(std::string name);
    std::shared_ptr<sf::Music> getMusic(int id);
};

#endif
