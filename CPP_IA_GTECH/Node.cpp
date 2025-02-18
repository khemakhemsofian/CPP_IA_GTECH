#include "Node.h"
#include <cmath>

Node::Node(sf::Vector2i pos) : position(pos), gCost(0), hCost(0), fCost(0), parent(nullptr) {}

void Node::calculateCosts(Node* end, int newG) {
    gCost = newG;
    int dx = position.x - end->position.x;
    int dy = position.y - end->position.y;
    hCost = std::sqrt(dx * dx + dy * dy);  // Distance Euclidienne
    fCost = gCost + hCost;
}