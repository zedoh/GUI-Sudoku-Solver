#include <SFML/Graphics.hpp>
#include "Headers/sudoku_grid.h"
#include <iostream>

int main() {
    // Create the SFML window
    sf::RenderWindow window(sf::VideoMode(800, 540), "SUDOKU");
    sf::Font font; 
    font.loadFromFile("font.ttf");
    // Create the Sudoku grid
    SudokuGrid SudokuGrid(font);
    bool SOLVED = 0 ; 
        int x{ 0 }; 
        int y{ 0 }; 
    // Main loop
    while (window.isOpen()) {
        // Process events
        sf::Event event;
        sf::Vector2i mousePosition;
        while (window.pollEvent(event)) {
            // Handle window closed event
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close(); 
            }
            else if (event.type == sf::Event::MouseMoved) {
                 mousePosition = sf::Mouse::getPosition(window);
                 SudokuGrid.handleMouseMovement(mousePosition); 
                 continue;
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                 mousePosition = sf::Mouse::getPosition(window);
                 auto Coordinates = SudokuGrid.handleMouseClicked(mousePosition); 
                 x = Coordinates.first; 
                 y = Coordinates.second;
                 SudokuGrid.ButtonClicked(mousePosition);
                 SudokuGrid.ClearButtonClicked(mousePosition);
            }
            else if (event.type == sf::Event::KeyPressed) {
                SudokuGrid.handleKeyboardPressed(event.key,x,y); 
            }

        }

        // Clear the window
        window.clear(sf::Color(69,48,40));

        // Draw the Sudoku grid
        SudokuGrid.draw(window);

        // Display the window contents
        window.display();
    }

    return 0;
}
