#include "datastorage.hpp"
#include "game.hpp"
#include "textRenderer.hpp"

DataStorage::DataStorage()
{
    fprintf(stderr, "# DataStorage: Constructing\n");
}

DataStorage::~DataStorage()
{
}

void DataStorage::loadData()
{
    game.getTextRenderer()->renderText(20, 20, "Loading graphics", FONT_SIZE::LARGE_FONT, true, sf::Color::Magenta);
    game.forceRedraw();
    
    loadTexture("player", "data/gfx/player.png");

    game.getRenderWindow()->clear();
    game.getTextRenderer()->renderText(20, 20, "Loading music", FONT_SIZE::LARGE_FONT, true, sf::Color::Magenta);
    game.forceRedraw();
    
    loadMusic(1, "data/music/game_song.ogg");
}

/**
* Loads a new texture from the given path and stores the produced Texture in the textureMap as a shared_ptr
* The texture is stored based on the given name
* Returns 1 if error, 0 if success
*/
int DataStorage::loadTexture(std::string name, std::string path)
{
    std::shared_ptr<sf::Texture> texture = std::shared_ptr<sf::Texture>(new sf::Texture());
    if (!texture->loadFromFile(path))
    {
        fprintf(stderr, "! DataStorage: Error loading file: %s\n", path.c_str());
        return 1;
    }
    textureMap[name] = texture;
    fprintf(stderr, "+DataStorage: Successfully loaded %s as %s\n", path.c_str(), name.c_str());
    return 0;
}

int DataStorage::loadMusic(int id, std::string path)
{
    std::shared_ptr<sf::Music> music = std::shared_ptr<sf::Music>(new sf::Music());
    if (!music->openFromFile(path.c_str()))
    {
        fprintf(stderr, "! DataStorage: Failed to load music %s\n", path.c_str());
        return 1;
    }
    return 0;
}

std::shared_ptr<sf::Texture> DataStorage::getTexture(std::string name)
{
    return nullptr;
}

std::shared_ptr<sf::Music> DataStorage::getMusic(int id)
{
    return nullptr;
}

