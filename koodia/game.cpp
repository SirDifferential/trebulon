#include "game.hpp"
#include "world.hpp"
#include "textRenderer.hpp"
#include "datastorage.hpp"
#include "player.hpp"
#include "toolbox.hpp"

Game game;

Game::Game()
{
    resolution_x = 800;
    resolution_y = 640;
    stop_running = false;
    dataStorage = std::shared_ptr<DataStorage>(new DataStorage());
    toolbox = std::shared_ptr<Toolbox>(new Toolbox());
    center_view.setCenter(sf::Vector2f(400,300));
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
                    case sf::Keyboard::T:
                        // stuff here
                        break;
                    case sf::Keyboard::Num1:
                        player->setDesiredSpeed(1);
                        break;
                    case sf::Keyboard::Num2:
                        player->setDesiredSpeed(2);
                        break;
                    case sf::Keyboard::Num3:
                        player->setDesiredSpeed(3);
                        break;
                    case sf::Keyboard::Num4:
                        player->setDesiredSpeed(4);
                        break;
                    case sf::Keyboard::Num5:
                        player->setDesiredSpeed(5);
                        break;
                    case sf::Keyboard::Num6:
                        player->setDesiredSpeed(6);
                        break;
                    case sf::Keyboard::Num7:
                        player->setDesiredSpeed(7);
                        break;
                    case sf::Keyboard::Num8:
                        player->setDesiredSpeed(8);
                        break;
                    case sf::Keyboard::Num9:
                        player->setDesiredSpeed(9);
                        break;
                    case sf::Keyboard::Num0:
                        player->setDesiredSpeed(0);
                        break;
                    break;
                }
                break;
        }

        // Events for keys that are held down
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            player->rotateLeft();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            player->rotateRight();
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
    fprintf(stderr, "# Game: Starting up\n");
    fprintf(stderr, "# Game: Creating window\n");
    mainWindow = std::shared_ptr<sf::RenderWindow>(new sf::RenderWindow());
    mainWindow->create(sf::VideoMode(resolution_x, resolution_y), "Water miners of Trebulon");
    mainWindow->setFramerateLimit(60);
    fprintf(stderr, "# Game: Initial window display\n");
    mainWindow->display();
    textRenderer = std::shared_ptr<TextRenderer>(new TextRenderer());
    game.getTextRenderer()->renderText(20, 20, "Loading data", FONT_SIZE::LARGE_FONT, true, sf::Color::Cyan);

    fprintf(stderr, "# Game: Loading content\n");
    dataStorage->loadData();

    game_music = dataStorage->getMusic(1);
    if (game_music != nullptr)
    {
        game_music->setLoop(true);
        game_music->play();
    }
    else
    {
        fprintf(stderr, "! Error playing music 0\n");
    }

    fprintf(stderr, "# Game: Creating world\n");
    world = std::shared_ptr<World>(new World());
    mainWindow->clear();
    getTextRenderer()->renderText(20, 20, "Creating world\nplease wait warmly", FONT_SIZE::LARGE_FONT, true, sf::Color::Magenta);
    forceRedraw();
    
    world->createWorld();

    player = std::shared_ptr<Player>(new Player());
    player->setPosition(200,200);
}

void Game::renderAll()
{
    world->render();
    player->render();
}

void Game::updateAll()
{
    world->update();
    player->update();
    center_view.setCenter(player->getPosition());
    mainWindow->setView(center_view);
}

/**
* Draws the main window right here and now
* Used during loading the game
*/
void Game::forceRedraw()
{
    mainWindow->display();
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
        updateAll();
        mainWindow->clear();
        renderAll();
        mainWindow->display();
    }
    return 0;
}

std::shared_ptr<sf::RenderWindow> Game::getRenderWindow()
{
    return mainWindow;
}

std::shared_ptr<TextRenderer> Game::getTextRenderer()
{
    return textRenderer;
}

std::shared_ptr<DataStorage> Game::getDataStorage()
{
    return dataStorage;
}

std::shared_ptr<Toolbox> Game::getToolbox()
{
    return toolbox;
}
