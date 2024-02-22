#pragma once

#include "grid.h"
#include "solver.h"
#include <utility>

struct Button {
    sf::RectangleShape      button; 
    sf::Text                label; 
    sf::Font                font; 
    sf::Texture             tex; 

    Button(const std::string &text ,const sf::Vector2f& Position, const sf::Vector2f& size, const std::string &type);
    void CenterButtonLabel(); 
    void drawButton(sf::RenderWindow& window); 
    sf::Texture settex(sf::Texture& tex, const std::string& path);
    void HoverButton(const sf::Vector2i &MousePosition); 

};

class SudokuGrid {
private:
    std::vector<std::vector<std::shared_ptr<Cell>>>     cells;
    std::shared_ptr<Button>                             button;  // Solve Button
    std::shared_ptr<Button>                             ClearButton; // Clear Button
    std::shared_ptr<Button>                             GameState; // [Can't Solve - Solved!]
    std::vector<std::shared_ptr<sf::RectangleShape>>    Lines;  //drawing thick lines to separate subgrids
    int                                                 SelectedRow; // Handling the position of the selected cell after executing the mouse clicking events
    int                                                 SelectedCol; 
    Solver                                              solver;

    void drawSubgrid(sf::RenderWindow& window)const;
public:
    SudokuGrid(const sf::Font& font);

    // Handling Varoius Events 
    void                draw(sf::RenderWindow& window) const;
    void                handleMouseMovement(const sf::Vector2i& mousePosition);
    std::pair<int,int>  handleMouseClicked(const sf::Vector2i& mousePosition); 
    void                handleKeyboardPressed(sf::Event::KeyEvent keyEvent , int x , int y); 
    bool                ButtonClicked(const sf::Vector2i& mousePosition);
    void                ClearButtonClicked(const sf::Vector2i &MousePosition); 
    
    // Utility Functions For Getting the current Grid value
    std::vector<std::vector<int>>   GridValues(); 
    void                            printValues() ;



    // Validations Functions before Solving
    //Checking Every Row , Col and Subgrid for inputs by the user before solving the sudoku
    bool CheckRow(GRID& grid, int row);
    bool CheckColumn(GRID& grid, int col);
    bool CheckSubgrid(GRID& grid, int startRow, int startCol);
    bool CheckGridBeforeSolving(GRID &grid); 

};
