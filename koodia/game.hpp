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
class Player;
class Toolbox;

class Game
{
private:
    std::shared_ptr<sf::RenderWindow> mainWindow;
    std::shared_ptr<TextRenderer> textRenderer;
    std::shared_ptr<DataStorage> dataStorage;
    std::shared_ptr<Player> player;
    std::shared_ptr<Toolbox> toolbox;
    
    int resolution_x;
    int resolution_y;
    bool stop_running;
    std::shared_ptr<World> world;
    std::shared_ptr<sf::Music> game_music;
    sf::View center_view;
public:
    Game();
    ~Game();
    void start();
    int mainloop();
    void updateAll();
    void renderAll();
    void checkEvents();
    void exit();

    void forceRedraw();

    std::shared_ptr<sf::RenderWindow> getRenderWindow();
    std::shared_ptr<TextRenderer> getTextRenderer();
    std::shared_ptr<DataStorage> getDataStorage();
    std::shared_ptr<Player> getPlayer();
    std::shared_ptr<Toolbox> getToolbox();
};

extern Game game;

#endif
