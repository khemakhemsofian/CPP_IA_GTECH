#include <SFML/Graphics.hpp>
#include <iostream>
#include "PNJ.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Détection PNJ");
    std::vector<sf::Vector2f> waypoints = { sf::Vector2f(100, 300), sf::Vector2f(500, 300), sf::Vector2f(300, 100), sf::Vector2f(200, 400), sf::Vector2f(600, 200) };
    PNJ pnj(sf::Vector2f(400, 300), 100.0f, 0.5f, 0.25f, 0.1f, 5.0f, waypoints);
    sf::CircleShape player(10);
    player.setFillColor(sf::Color::Blue);

    sf::Vector2f playerPos(100, 100);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) playerPos.x += 0.25f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) playerPos.x -= 0.25f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) playerPos.y += 0.25f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) playerPos.y -= 0.25f;

        player.setPosition(playerPos);

        pnj.update(playerPos);

        window.clear();
        window.draw(player);
        pnj.draw(window);
        window.display();
    }

    return 0;
}