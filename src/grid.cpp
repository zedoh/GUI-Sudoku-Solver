#include "../Headers/grid.h"

Cell::Cell(int value, const sf::Font& font, const sf::Vector2f& position, float size)
    : value(value), hovered(false), shape(sf::Vector2f(size, size)), text(std::to_string(value), font),fixed(false) {
    shape.setPosition(position);
    shape.setOutlineThickness(2);
    shape.setOutlineColor(sf::Color::Black);
    shape.setFillColor(sf::Color(58, 68, 102));

    text.setPosition(position.x + size / 2 - text.getLocalBounds().width / 2,
        position.y + size / 2 - text.getLocalBounds().height / 2);
    text.setFillColor(sf::Color::White);

}

void Cell::setValue(int value) {
    this->value = value;
    if (value == 0) {
		// reset values for Default
        text.setString(""); 
        text.setFillColor(sf::Color::White); 
    }
    text.setString(std::to_string(value));
}

void Cell::setHovered(bool hovered) {
    this->hovered = hovered;
    shape.setFillColor(hovered ? sf::Color(155, 146, 207) : sf::Color(58, 68, 102));
}

bool Cell::contains(const sf::Vector2f& point) const {
    return shape.getGlobalBounds().contains(point);
}

int Cell::getValue()const {
    return this->value; 
}

void Cell::setFixed(bool value)
{
    this->fixed = value; 
}

bool Cell::getFixed() const
{
    return this->fixed;
}

void Cell::UserTextColor()
{
    text.setFillColor(sf::Color::Green); 
}

void Cell::draw(sf::RenderWindow& window) const {
    if (getValue() == 0) {
		window.draw(shape);
    }
    else {
		window.draw(shape);
		window.draw(text);
    }
}
