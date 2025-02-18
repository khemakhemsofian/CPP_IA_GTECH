#ifndef PNJ_H
#define PNJ_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Grid.h"

class PNJ {
public:
    sf::Vector2i position;
    std::vector<sf::Vector2i> path;
    int pathIndex;
    sf::Clock moveClock;
    bool needsRepath;

    PNJ(sf::Vector2i start);
    void update(Grid& grid, sf::Vector2i target);
    void draw(sf::RenderWindow& window);
};

#endif
