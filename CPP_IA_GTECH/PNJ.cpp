#include "PNJ.h"
#include "Pathfinding.h"

PNJ::PNJ(sf::Vector2i start) : position(start), pathIndex(0) {}

void PNJ::update(Grid& grid, sf::Vector2i target) {
    if (!path.empty() && grid.grid[path[pathIndex].y][path[pathIndex].x] == 1) {
        needsRepath = true;
    }

    if (needsRepath || path.empty()) {
        path = Pathfinding::findPath(grid, position, target);
        pathIndex = 0;
        needsRepath = false;
    }

    if (moveClock.getElapsedTime().asSeconds() < 0.5) {
        return;
    }
    moveClock.restart();

    if (!path.empty() && pathIndex < path.size()) {
        position = path[pathIndex];
        if (pathIndex != path.size() - 1)
            pathIndex++;
    }
}

void PNJ::draw(sf::RenderWindow& window) {
    sf::CircleShape shape(15);
    shape.setPosition(position.x * CELL_SIZE + 10, position.y * CELL_SIZE + 10);
    shape.setFillColor(sf::Color::Red);
    window.draw(shape);
}



