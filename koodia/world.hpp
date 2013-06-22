#include <memory>
#include <SFML/Graphics.hpp>

class World
{
private:
    std::shared_ptr<sf::Texture> worldMapData;
    std::shared_ptr<sf::Sprite> worldMap;
public:
    World();
    ~World();

    void createWorld();
    void render();
};
