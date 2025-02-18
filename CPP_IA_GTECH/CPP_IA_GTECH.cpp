#include <SFML/Graphics.hpp>
#include "PNJ.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(GRID_WIDTH * CELL_SIZE, GRID_HEIGHT * CELL_SIZE), "Pathfinding");

    Grid grid;
    PNJ pnj({ 0, 0 });
    sf::Vector2i target(15, 10);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                // Ajouter/Supprimer des obstacles avec clic gauche
                if (event.mouseButton.button == sf::Mouse::Left) {
                    grid.handleClick(event.mouseButton.x, event.mouseButton.y);
                    pnj.needsRepath = true; // Demander un recalcul du chemin
                }

                // Définir un nouvel objectif avec clic droit
                if (event.mouseButton.button == sf::Mouse::Right) {
                    target = { event.mouseButton.x / CELL_SIZE, event.mouseButton.y / CELL_SIZE };
                    pnj.needsRepath = true;
                }
            }
        }

        pnj.update(grid, target);

        window.clear();
        grid.draw(window);
        pnj.draw(window);
        window.display();
    }

    return 0;
}
