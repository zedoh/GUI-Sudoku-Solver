#include "../Headers/Sodoku.h"


Sudoku::Sudoku(sf::Font &font):sudoku(font),window(sf::VideoMode(WINDOWWIDTH, WINDOWHEIGHT),"SUDOKU") {
	x = 0; 
	y = 0; 
	Run(); 
}


void Sudoku::GameLoop(sf::RenderWindow &window) {
	while (window.isOpen()) {
		sf::Event event; 
		sf::Vector2i mouseposition;

		while (window.pollEvent(event)) {
			// handle window close event

			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				window.close(); 
			}
			else if (event.type == sf::Event::MouseMoved) {
				mouseposition = sf::Mouse::getPosition(window); 
				sudoku.handleMouseMovement(mouseposition); 
				continue; 
			}
			else if (event.type == sf::Event::MouseButtonPressed) {
				mouseposition = sf::Mouse::getPosition(window); 
				auto coordinates = sudoku.handleMouseClicked(mouseposition);
				x = coordinates.first; 
				y = coordinates.second; 
				sudoku.ButtonClicked(mouseposition); 
				sudoku.ClearButtonClicked(mouseposition); 
			}
			else if (event.type == sf::Event::KeyPressed) {
				sudoku.handleKeyboardPressed(event.key, x, y);
			}
		}
		window.clear(sf::Color(69, 48, 40)); 
		sudoku.draw(window); 
		window.display(); 
	}
}

void Sudoku::Run() {
	GameLoop(window); 
}
