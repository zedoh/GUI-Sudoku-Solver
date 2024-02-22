#pragma once
#include "sudoku_grid.h"

const unsigned int WINDOWWIDTH{ 800 }; 
const unsigned int WINDOWHEIGHT{ 540 }; 
const std::string FONTPATH{ "Resources/font.ttf" }; 


class Sudoku {
private:
	SudokuGrid			sudoku;
	sf::RenderWindow	window;
	sf::Font			font; 
	int					x; // selected clicked cell position on  the x-axis
	int					y; // selected clicked cell position on the y-axis
public:
	Sudoku(sf::Font &font);
	void GameLoop(sf::RenderWindow& window); 

	void Run(); 
};
