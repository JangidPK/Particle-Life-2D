#include<text.h>


Text::Text(const std::string& fontPath, const std::string& text, unsigned int characterSize, const sf::Vector2f& position) {
    if (!font.loadFromFile(fontPath)) {
        throw std::runtime_error("Failed to load font");
    }

    this->text.setFont(font);
    this->text.setString(text);
    this->text.setCharacterSize(characterSize);
    this->text.setFillColor(sf::Color::White);
    this->text.setPosition(position);
}

void Text::setText(const std::string& newText) {
    text.setString(newText);
}

void Text::setPosition(const sf::Vector2f& newPosition) {
    text.setPosition(newPosition);
}

void Text::setColor(const sf::Color& color) {
    text.setFillColor(color);
}

void Text::draw(sf::RenderWindow& window)  {
    window.draw(text);
}

