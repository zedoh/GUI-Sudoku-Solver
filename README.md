# Suduko Solver
- It is a sudoku solver gui game made using **SFML**, **C++**
- [Backtracking Algorithm](https://en.wikipedia.org/wiki/Backtracking) is used to solve the sudoku grid.

# Preview
https://github.com/zedoh/PRODIGY_SD_04/assets/48362347/8d05a63d-8e5b-40de-9db8-54c82859153b
# Controls
- `Left click` on the cell to give a value.
- `Left click` + `DEL` to delete a value
- `ESC` to close the game
# Datastructures and Algorithms 
| Data Structure / Algorithm | Description | Example Usage |
| -------------------------- | ----------- | ------------- |
| Grid                       | Represents the Sudoku grid as a 2D array of integers. | Storing and manipulating the Sudoku puzzle. |
| Backtracking Algorithm     | Recursive algorithm used to solve the Sudoku puzzle. | Solving the Sudoku puzzle efficiently. |
| Button Class               | Represents interactive buttons in the GUI. | Creating buttons for solving and clearing the Sudoku grid. |
| Cell Class                 | Represents individual cells in the Sudoku grid. | Handling user input and displaying cell values. |

# UML Class Diagram
```mermaid
classDiagram
    class SudokuGrid {
        - cells : std::vector<std::vector<std::shared_ptr<Cell>>>
        - button : Button
        - ClearButton : Button 
        - GameState : Button
        - Lines : std::vector<sf::RectangleShape>
        - SelectedRow : int 
        - SelectedCol : int 
        - solver : Solver
        - drawSubgrid(window : sf::RenderWindow&) const
        + SudokuGrid(font : const sf::Font&)
        + draw(window : sf::RenderWindow&) const
        + handleMouseMovement(mousePosition : const sf::vector2i&)
        + handleMouseClicked(mousePosition : const sf::vector2i&) std::pair<int,int>
        + handleKeyboardPressed(keyEvent : sf::Event::KeyEvent , x : int , y:int)
        + ButtonClicked(mousePosition : const sf::Vector2i&) bool
        + ClearButtonClicked(MousePosition : const sf::Vector2i &)
        + GridValues() GRID
        + printValues()
        + CheckRow(grid : GRID&, row : int) bool
        + CheckColumn(grid : GRID&, col : int) bool
        + CheckSubgrid(grid : GRID&, startRow : int, startCol : int) bool
        + CheckGridBeforeSolving(grid : GRID&) bool
    }
    
    class Cell {
        - value : int
        - hovered : bool
        - fixed : bool
        - shape : sf::RectangleShape
        - text  : sf::text
        + Cell(value : int, font : const sf::Font&, position : const sf::Vector2f&, size : float)
        + setValue(value : int)
        + setHovered(hovered : bool)
        + setFixed(value : bool)
        + contains(point : const sf::Vector2f&) bool const
        + getFixed() bool const
        + getValue() int const
        + draw(window : sf::RenderWindow&) const 
        + UserTextColor() 
    }
    
    class Button {
        + button : sf::RectangleShape
        + label : sf::Text
        + font  : sf::Font
        + tex : sf::Texture
        +Button(text : const std::string&, Position : const sf::Vector2f&, size : const sf::Vector2f&, type : const std::string&)
        +CenterButtonLable()
        +drawButton(window : sf::RenderWindow&)
        +HoverButton(MousePosition : const sf::Vector2i&)
    }

    class Sudoku {
        - sudoku : SudokuGrid
        - window : sf::RenderWindow
        - font : sf::Font 
        - x : int
        - y : int
        + Sudoku(font : sf::Font&)
        + GameLoop(window : sf::RenderWindow&)
        + Run()
    }

    class Solver {
        + is_valid(grid : const GRID&, r : int, k : int) bool
        + solve(cells : const GRID&, r : int, c : int)
    }

    SudokuGrid *-- Cell
    SudokuGrid o-- Solver
    SudokuGrid *-- Button
    Sudoku *-- SudokuGrid
```
