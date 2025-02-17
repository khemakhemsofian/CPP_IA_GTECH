#include "PNJ.h"

PNJ::PNJ(sf::Vector2f startPos, float radius, float patrolSpeed, float chaseSpeed,float searchSpeed ,float waypointThreshold, const std::vector<sf::Vector2f>& waypoints)
    : position(startPos), detectionRadius(radius), patrolSpeed(patrolSpeed), chaseSpeed(chaseSpeed),searchSpeed(searchSpeed), waypointThreshold(waypointThreshold),waypoints(waypoints), currentWaypoint(0), currentState(PATROL), searchDuration(3.0f) {
    color = sf::Color::Red;
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

bool PNJ::detectPlayer(sf::Vector2f playerPos) {
    float distance = std::sqrt(std::pow(playerPos.x - position.x, 2) + std::pow(playerPos.y - position.y, 2));
    return distance <= detectionRadius;
}

void PNJ::draw(sf::RenderWindow& window) {
    sf::CircleShape shape(10);
    shape.setFillColor(color);
    shape.setPosition(position);
    window.draw(shape);
}

void PNJ::patrol() {
    std::cout << "Patrolling..." << std::endl; // Message de console pour la patrouille
    if (waypoints.empty()) return;

    sf::Vector2f target = waypoints[currentWaypoint];
    sf::Vector2f direction = target - position;
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (length != 0) {
        direction /= length;
    }

    position += direction * patrolSpeed;

    if (length < patrolSpeed) {
        currentWaypoint = (currentWaypoint + 1) % waypoints.size();
    }
}

void PNJ::chase(sf::Vector2f playerPos) {
    std::cout << "Chasing player..." << std::endl; // Message de console pour la poursuite
    sf::Vector2f direction = playerPos - position;
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    float adjustedChaseSpeed = chaseSpeed * (detectionRadius / length); // Ajuster la vitesse en fonction de la distance
    if (length > minDistance) {
        if (length != 0) {
            direction /= length;
        }

        position += direction * adjustedChaseSpeed;
    }
}

void PNJ::search() {
    std::cout << "Searching..." << std::endl; // Message de console pour la recherche
    // Mouvement aléatoire léger
    float angle = static_cast<float>(std::rand() % 360); // Angle aléatoire en degrés
    float radian = angle * 3.14159f / 180.0f; // Convertir en radians
    sf::Vector2f direction(std::cos(radian), std::sin(radian));

    position += direction * searchSpeed;
}

void PNJ::update(sf::Vector2f playerPos) {
    switch (currentState) {
    case PATROL:
        std::cout << "Current State: PATROL" << std::endl; // Message de console pour l'état PATROL
        patrol();
        if (detectPlayer(playerPos)) {
            currentState = CHASE;
        }
        break;
    case CHASE:
        std::cout << "Current State: CHASE" << std::endl; // Message de console pour l'état CHASE
        chase(playerPos);
        if (!detectPlayer(playerPos)) {
            currentState = SEARCH;
            searchClock.restart(); // Redémarrer le timer de recherche
        }
        break;
    case SEARCH:
        std::cout << "Current State: SEARCH" << std::endl; // Message de console pour l'état SEARCH
        search();
        if (searchClock.getElapsedTime().asSeconds() >= searchDuration) {
            currentState = PATROL;
        }
        break;
    }
}