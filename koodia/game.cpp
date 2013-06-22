#include "game.hpp"
#include "world.hpp"
Game game;

Game::Game()
{
    resolution_x = 800;
    resolution_y = 640;
    stop_running = false;
}

Game::~Game()
{
}

/**
* Handles window, keyboard and mouse events
*/
void Game::checkEvents()
{
    sf::Event e;
    while (mainWindow->pollEvent(e))
    {
        switch (e.type)
        {
            case sf::Event::Closed:
                exit();
                break;
            case sf::Event::KeyReleased:
                switch (e.key.code)
                {
                    case sf::Keyboard::T:
                        // stuff here
                        break;
                }
                break;
            case sf::Event::KeyPressed:
                switch (e.key.code)
                {
                    case sf::Keyboard::Escape:
                        exit();
                        break;
                }
            break;
        }
    }
}

void Game::exit()
{
    stop_running = true;
    mainWindow->close();
}

void Game::start()
{
    mainWindow = std::shared_ptr<sf::RenderWindow>(new sf::RenderWindow());
    mainWindow->create(sf::VideoMode(resolution_x, resolution_y), "jokunimitähän");
    mainWindow->setFramerateLimit(60);
    mainWindow->display();

    world = std::shared_ptr<World>(new World());
    world->createWorld();
}

void Game::renderAll()
{
    world->render();
}

int Game::mainloop()
{
    int fps = 0;
    int nextFPS = 3;
    sf::Clock fps_clock;
    sf::Clock main_clock;

    while (stop_running == false)
    {
        fps = 1 / fps_clock.getElapsedTime().asSeconds();
        fps_clock.restart();
        if (main_clock.getElapsedTime().asSeconds() > nextFPS)
        {
            nextFPS += 1;
            fprintf(stderr, "%d\n", fps);
        }
        checkEvents();
        renderAll();
        mainWindow->display();
    }
    return 0;
}

std::shared_ptr<sf::RenderWindow> Game::getRenderWindow()
{
    return mainWindow;
}
