#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

class Cell {
private:
    int					value;
    bool				hovered;
	bool				fixed; //value entered by the user and can't be changed while generating the solution
    sf::RectangleShape	shape;
    sf::Text			text;
public:
    Cell(int value, const sf::Font& font, const sf::Vector2f& position, float size);

	// Setters
	void setValue(int value);
	void setHovered(bool hovered);
	void setFixed(bool value);

	bool contains(const sf::Vector2f& point) const;
	
	// Getters 
	bool getFixed()const; //returns wether the cell is fixed value or not
	int getValue()const;
	
	void draw(sf::RenderWindow& window) const;
	void UserTextColor(); // Separating the user input color from the solver input color

};
