#ifndef __GAME_HPP_
#define __GAME_HPP_

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include <vector>

class World;
class TextRenderer;
class DataStorage;

class Game
{
private:
    std::shared_ptr<sf::RenderWindow> mainWindow;
    std::shared_ptr<TextRenderer> textRenderer;
    std::shared_ptr<DataStorage> dataStorage;
    
    int resolution_x;
    int resolution_y;
    bool stop_running;
    std::shared_ptr<World> world;
    std::shared_ptr<sf::Music> game_music;
public:
    Game();
    ~Game();
    void start();
    int mainloop();
    void renderAll();
    void checkEvents();
    void exit();

    void forceRedraw();

    std::shared_ptr<sf::RenderWindow> getRenderWindow();
    std::shared_ptr<TextRenderer> getTextRenderer();
    std::shared_ptr<DataStorage> getDataStorage();
};

extern Game game;

#endif
