#include "datastorage.hpp"
#include "game.hpp"
#include "textRenderer.hpp"
#include <algorithm>
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
    loadTexture("banner", "data/gfx/banner.png");
    loadTexture("help", "data/gfx/keys.png");
    loadTexture("drill", "data/gfx/drill.png");
    loadTexture("probe", "data/gfx/probe.png");
    std::shared_ptr<sf::Sprite> drillImage = std::shared_ptr<sf::Sprite>(new sf::Sprite());
    drillImage->setTexture((*getTexture("drill")));
    spriteMap["drill"] = drillImage;

    std::shared_ptr<sf::Sprite> probeImage = std::shared_ptr<sf::Sprite>(new sf::Sprite());
    probeImage->setTexture((*getTexture("probe")));
    spriteMap["probe"] = probeImage;

    game.getRenderWindow()->clear();
    game.getTextRenderer()->renderText(20, 20, "Loading music", FONT_SIZE::LARGE_FONT, true, sf::Color::Magenta);
    game.forceRedraw();
    
    loadMusic(1, "data/music/song_game.ogg");
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
    musicMap[id] = music;
    return 0;
}

/**
* Returns an existing image from the imageMap, or NULL if not found
*/
std::shared_ptr<sf::Texture> DataStorage::getTexture(std::string name)
{
    std::map<std::string ,std::shared_ptr<sf::Texture> >::iterator it;
    it = textureMap.find(name);
    if (it == textureMap.end())
    {
        fprintf(stderr, "! DataStorage: Image not found: %s\n", name.c_str());
        return nullptr;
    }
    return it->second;
}

std::shared_ptr<sf::Music> DataStorage::getMusic(int id)
{
    std::map<int ,std::shared_ptr<sf::Music> >::iterator it;
    it = musicMap.find(id);
    if (it == musicMap.end())
    {
        fprintf(stderr, "! DataStorage: Music not found: %d\n", id);
        return nullptr;
    }
    return it->second;
}

std::shared_ptr<sf::Sprite> DataStorage::getSprite(std::string name)
{
    std::map<std::string ,std::shared_ptr<sf::Sprite> >::iterator it;
    it = spriteMap.find(name);
    if (it == spriteMap.end())
    {
        fprintf(stderr, "! DataStorage: Image not found: %s\n", name.c_str());
        return nullptr;
    }
    return it->second;
}
