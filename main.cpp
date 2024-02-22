#include <SFML/Graphics.hpp>
#include "Headers/Sodoku.h"
#include <iostream>

int main() {
	sf::Font font; 
	font.loadFromFile("Resources/font.ttf"); 
	Sudoku sudoku(font); 
}
