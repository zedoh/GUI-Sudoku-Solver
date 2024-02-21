#include "../Headers/sudoku_grid.h"
#include <iostream>


// Position of the Grid
const sf::Vector2f POSITION_GRID    { 50.0f , 50.0f };
const sf::Vector2f SOLVEBUTTONPOS   { 550.0f , 50.0f }; 
const sf::Vector2f CLEARBUTTONPOS   { 550.0f , 150.0f }; 

Button::Button(const std::string &text,const sf::Vector2f &Position) {
    font.loadFromFile("font.ttf"); 
    if (!tex.loadFromFile("button.png")) {
        std::cerr << "\nCan't load this texture"; 
    }
    button.setTexture(&tex); 
    label.setFont(font); 
    label.setCharacterSize(22);
    label.setString(text); 
    label.setStyle(sf::Text::Bold);
    label.setFillColor(sf::Color::White); 
    button.setSize({ 200.0f , 50.0f }); 
    button.setPosition(Position); 
    CenterButtonLabel(); 
}

SudokuGrid::SudokuGrid(const sf::Font& font) {
    float cellSize = 50.0f; 
    for (int i = 0; i < 9; ++i) {
        std::vector<std::shared_ptr<Cell>> row;
        for (int j = 0; j < 9; ++j) {
            row.emplace_back(std::make_shared<Cell>( 0 , font, POSITION_GRID+ sf::Vector2f(j * cellSize, i * cellSize), cellSize));
        }
        cells.push_back(std::move(row));
    }

    Lines.resize(4);  //4 lines only (2 horizontal, 2 Vertical)
	for (int i = 0; i < 4; ++i) {
		Lines[i] = std::make_shared<sf::RectangleShape>();
	}

    button = std::make_shared<Button>("Solve", SOLVEBUTTONPOS);
    ClearButton = std::make_shared<Button>("Clear",CLEARBUTTONPOS);
    SelectedCol = 0; 
    SelectedRow = 0; 
}

void SudokuGrid::drawSubgrid(sf::RenderWindow& window) const{
    // Drawing the Horizontal lines separators 
    for (int i = 0, j = 1; i < 2; i++, j++) {
    Lines[i]->setPosition(POSITION_GRID.x + j*(3 * 50), POSITION_GRID.y); 
    Lines[i]->setSize(sf::Vector2f(1, 450)); 
    Lines[i]->setFillColor(sf::Color::Black); 
    Lines[i]->setOutlineThickness(2); 
    Lines[i]->setOutlineColor(sf::Color::Black);
    }

    // Drawing the Vertical lines separators 
    for (int i = 2, j = 1; i < 4; i++, j++) {
    Lines[i]->setPosition(POSITION_GRID.x, POSITION_GRID.y + j*(3*50)); 
    Lines[i]->setSize(sf::Vector2f(450, 1)); 
    Lines[i]->setFillColor(sf::Color::Black); 
    Lines[i]->setOutlineThickness(2); 
    Lines[i]->setOutlineColor(sf::Color::Black);
    }

    // Rendering all the lines
    for (int i = 0; i < 4; ++i) {
        window.draw(*Lines[i]); 
    }
}

void SudokuGrid::handleMouseMovement(const sf::Vector2i& mousePosition) {
    for (auto& row : cells) {
        for (auto& cell : row) {
            cell->setHovered(cell->contains(static_cast<sf::Vector2f>(mousePosition)));
        }
    }
    button->HoverButton(mousePosition);
    ClearButton->HoverButton(mousePosition); 
}

std::pair<int, int> SudokuGrid::handleMouseClicked(const sf::Vector2i& mousePosition) {
    for (int i = 0; i < (int)cells.size(); ++i) {
        for (int j = 0; j < (int)cells.size(); ++j) {
            if (cells[i][j]->contains(static_cast<sf::Vector2f>(mousePosition))) {
                this->SelectedRow = i; 
                this->SelectedCol = j;
                break;
            }
        }
    }

    // for Debugging purposes
    std::cout << SelectedRow << " " << SelectedCol << '\n'; 
    std::cout << std::boolalpha << cells[SelectedRow][SelectedCol]->getFixed() << '\n'; 
    return { SelectedRow, SelectedCol };
}

bool SudokuGrid::ButtonClicked(const sf::Vector2i& mousePosition) {
    std::vector<std::vector<int>>values = GridValues(); 
	sf::FloatRect ButtonBounds = button->button.getGlobalBounds();
	bool check = CheckGridBeforeSolving(values); 
	if (ButtonBounds.contains(static_cast<sf::Vector2f>(mousePosition))) {
		if (check == true) {
			solver.solve(values, 0, 0);
			for (int i = 0; i < (int)cells.size(); ++i) {
				for (int j = 0; j < (int)cells[0].size(); ++j) {
					if (cells[i][j]->getValue() == 0) {
						cells[i][j]->setValue(values[i][j]);
						cells[i][j]->setFixed(true);
					}
				}
			}
			return true;
		}
		else {
			std::cerr << "\nCan't Solve [INVALID INPUT]\n"; 
			return false; 
		}

	}
	return false;
}


// Handling user inputs (numbers)
void SudokuGrid::handleKeyboardPressed(sf::Event::KeyEvent keyEvent, int x, int y)
{
	sf::Keyboard::Key key = keyEvent.code;
	int currentValue = cells[x][y]->getValue();
	bool fixedValue = cells[x][y]->getFixed();
	if (key >= sf::Keyboard::Num1 && key <= sf::Keyboard::Num9 && currentValue == 0) {
		int number = key - sf::Keyboard::Num0;
		cells[x][y]->setValue(number);
		cells[x][y]->UserTextColor();
		cells[x][y]->setFixed(false);
	}
	// User Shouldn't delete any element from the generated solution
	// User should only delete his inputs
	else if (key == sf::Keyboard::Delete) {
		if (fixedValue == false) {
			cells[x][y]->setValue(0);
			cells[x][y]->setFixed(false);
		}
	}

	std::cout << "\nCurrent Grid Values\n";
	printValues();
}




void SudokuGrid::draw(sf::RenderWindow& window) const {
	for (const auto& row : cells) {
		for (const auto& cell : row) {
			cell->draw(window);
		}
	}
	button->drawButton(window);
	ClearButton->drawButton(window);
	drawSubgrid(window);
}

std::vector<std::vector<int>> SudokuGrid::GridValues()
{
	std::vector<std::vector<int>> values(cells.size(), std::vector<int>(cells[0].size()));

	for (int i = 0; i < (int)cells.size(); ++i) {
		for (int j = 0; j < cells[0].size(); ++j) {
			values[i][j] = cells[i][j]->getValue();
		}
	}

	return values;
}

void SudokuGrid::printValues() {
	std::vector<std::vector<int>> values = GridValues();
	for (auto row : values) {
		for (auto col : row) {
			std::cout << col << " ";
		}
		std::cout << '\n';
	}
}
bool SudokuGrid::CheckRow(GRID& grid, int row)
{
	std::vector<bool> seen(10, false); // 1-based indexing

	for (int j = 0; j < 9; ++j) {
		int value = grid[row][j];
		if (value != 0 && seen[value]) {
			return false; // Duplicate value found
		}
		seen[value] = true;
	}

	return true;
}

bool SudokuGrid::CheckColumn(GRID& grid, int col)
{
	std::vector<bool> seen(10, false); 

	for (int i = 0; i < 9; ++i) {
		int value = grid[i][col];
		if (value != 0 && seen[value]) {
			return false; 
		}
		seen[value] = true;
	}

	return true;
}

bool SudokuGrid::CheckSubgrid(GRID& grid, int startRow, int startCol)
{
	std::vector<bool> seen(10, false); 

	for (int i = startRow; i < startRow + 3; ++i) {
		for (int j = startCol; j < startCol + 3; ++j) {
			int value = grid[i][j];
			if (value != 0 && seen[value]) {
				return false; 
			}
			seen[value] = true;
		}
	}

	return true;
}


bool SudokuGrid::CheckGridBeforeSolving(GRID& grid)
{
	// Check rows
	for (int i = 0; i < 9; ++i) {
		if (!CheckRow(grid, i)) {
			std::cerr << "Error: Invalid row at index " << i << std::endl;
			return false;
		}
	}

	// Check columns
	for (int j = 0; j < 9; ++j) {
		if (!CheckColumn(grid, j)) {
			std::cerr << "Error: Invalid column at index " << j << std::endl;
			return false;
		}
	}

	// Check subgrids
	for (int i = 0; i < 9; i += 3) {
		for (int j = 0; j < 9; j += 3) {
			if (!CheckSubgrid(grid, i, j)) {
				std::cerr << "Error: Invalid subgrid starting at (" << i << ", " << j << ")" << std::endl;
				return false;
			}
		}
	}

	return true;

}



void Button::CenterButtonLabel()
{
	sf::FloatRect textBounds = label.getLocalBounds();
	sf::FloatRect buttonBounds = button.getLocalBounds();

	float CenterX = button.getPosition().x + button.getSize().x / 2 - textBounds.width / 2;
	float CenterY = button.getPosition().y + button.getSize().y / 2 - textBounds.height / 2;

	label.setPosition(CenterX, CenterY);
}

void Button::drawButton(sf::RenderWindow& window)
{
	window.draw(button);
	window.draw(label);
}

void Button::HoverButton(const sf::Vector2i& MousePosition)
{
	if (button.getGlobalBounds().contains(static_cast<sf::Vector2f>(MousePosition))) {
		label.setFillColor(sf::Color::Black);
	}
	else {
		label.setFillColor(sf::Color::White);
	}
}

void SudokuGrid::ClearButtonClicked(const sf::Vector2i& MousePosition)
{
	if (ClearButton->button.getGlobalBounds().contains(static_cast<sf::Vector2f>(MousePosition))) {
		for (int i = 0; i < (int)cells.size(); ++i) {
			for (int j = 0; j < cells[0].size(); ++j) {
				cells[i][j]->setValue(0);
				cells[i][j]->setFixed(false);
			}
		}
	}
}
