#include "textRenderer.hpp"
#include "game.hpp"


TextRenderer::TextRenderer()
{
    if (!font1.loadFromFile("data/fonts/CursiveSans.ttf"))
    {
        fprintf(stderr, "!!!!!!TextRenderer: Could not load font\n");
    }
    else
    {
        fprintf(stderr, "+TextRenderer: Font built successfully\n");
    }
}

TextRenderer::~TextRenderer()
{
}

void TextRenderer::renderText(int x, int y, std::string message, FONT_SIZE s)
{
    float scale;

    switch (s)
    {
        case SMALL_FONT: scale = 0.4f; break;
        case MEDIUM_FONT: scale = 0.6f; break;
        case LARGE_FONT: scale = 1.0f; break;
        default: scale = 0.4f; break;
    }
    
    sf::Text text;

    text.setString(message);
    text.setFont(font1);
    text.setScale(scale, scale);
    text.setColor(sf::Color(255, 255, 255, 255));
    text.setPosition(x,y);
    game.getRenderWindow()->draw(text);
}

void TextRenderer::renderText(int x, int y, std::string message, FONT_SIZE s, bool bold)
{
    float scale;

    switch (s)
    {
        case SMALL_FONT: scale = 0.4f; break;
        case MEDIUM_FONT: scale = 0.6f; break;
        case LARGE_FONT: scale = 1.0f; break;
        default: scale = 0.4f; break;
    }
    
    sf::Text text;

    text.setString(message);
    text.setFont(font1);
    text.setScale(scale, scale);
    text.setColor(sf::Color(255, 255, 255, 255));
    text.setPosition(x,y);
    if (bold == true)
        text.setStyle(sf::Text::Style::Bold);
    game.getRenderWindow()->draw(text);
}

void TextRenderer::renderText(int x, int y, std::string message, FONT_SIZE s, bool bold, sf::Color c)
{
    float scale;

    switch (s)
    {
        case SMALL_FONT: scale = 0.4f; break;
        case MEDIUM_FONT: scale = 0.6f; break;
        case LARGE_FONT: scale = 1.0f; break;
        default: scale = 0.4f; break;
    }
    
    sf::Text text;

    text.setString(message);
    text.setFont(font1);
    text.setScale(scale, scale);
    text.setColor(c);
    text.setPosition(x,y);
    if (bold == true)
        text.setStyle(sf::Text::Style::Bold);
    game.getRenderWindow()->draw(text);
}
