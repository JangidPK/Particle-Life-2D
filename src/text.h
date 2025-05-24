#pragma  once

#include <SFML/Graphics.hpp>
#include <string>

class Text {
public:
    Text(const std::string& fontPath, const std::string& text, unsigned int characterSize, const sf::Vector2f& position) ;

    void setText(const std::string& newText);

    void setPosition(const sf::Vector2f& newPosition);
    void setColor(const sf::Color& color);

    void draw(sf::RenderWindow& window) ;

private:
    sf::Font font;
    sf::Text text;
};
