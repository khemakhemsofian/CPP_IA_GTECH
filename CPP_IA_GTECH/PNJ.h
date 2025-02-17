#ifndef PNJ_H
#define PNJ_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <iostream>
#include <cstdlib>  // Pour std::rand et std::srand

class PNJ {
public:
    sf::Vector2f position;
    float detectionRadius;
    sf::Color color;
    float patrolSpeed;
	float chaseSpeed;
	float searchSpeed;
    float waypointThreshold;
    std::vector<sf::Vector2f> waypoints;
    int currentWaypoint;
    const float minDistance = 75.0f;
	enum State { PATROL, CHASE, SEARCH };
	State currentState;
    sf::Clock searchClock;
    float searchDuration;

    PNJ(sf::Vector2f startPos, float radius, float patrolSpeed, float chaseSpeed,float searchSpeed,float waypointThreshold, const std::vector<sf::Vector2f>& waypoints);

    bool detectPlayer(sf::Vector2f playerPos);
	void update(sf::Vector2f playerPos);
    void draw(sf::RenderWindow& window);
	void patrol();
	void chase(sf::Vector2f playerPos);
	void search();
};

#endif