#include "Grid.h"

Grid::Grid() {
    grid.resize(GRID_HEIGHT, std::vector<int>(GRID_WIDTH, 0));

    // Définition de quelques obstacles
    for (int i = 5; i < 15; i++) {
        grid[7][i] = 1;
    }
}

void Grid::draw(sf::RenderWindow& window) {
    for (int y = 0; y < GRID_HEIGHT; y++) {
        for (int x = 0; x < GRID_WIDTH; x++) {
            sf::RectangleShape cell(sf::Vector2f(CELL_SIZE, CELL_SIZE));
            cell.setPosition(x * CELL_SIZE, y * CELL_SIZE);
            cell.setOutlineThickness(1);
            cell.setOutlineColor(sf::Color::Black);

            if (grid[y][x] == 1) {
                cell.setFillColor(sf::Color::Black);
            }
            else {
                cell.setFillColor(sf::Color::White);
            }

            window.draw(cell);
        }
    }
}

void Grid::handleClick(int mouseX, int mouseY) {
    int x = mouseX / CELL_SIZE;
    int y = mouseY / CELL_SIZE;

    if (x >= 0 && x < GRID_WIDTH && y >= 0 && y < GRID_HEIGHT) {
        grid[y][x] = (grid[y][x] == 0) ? 1 : 0;  // Bascule entre obstacle et case vide
    }
}