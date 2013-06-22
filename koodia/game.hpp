#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

class World;

class Game
{
private:
    std::shared_ptr<sf::RenderWindow> mainWindow;
    int resolution_x;
    int resolution_y;
    bool stop_running;
    std::shared_ptr<World> world;
public:
    Game();
    ~Game();
    void start();
    int mainloop();
    void renderAll();
    void checkEvents();
    void exit();

    std::shared_ptr<sf::RenderWindow> getRenderWindow();
};

extern Game game;
