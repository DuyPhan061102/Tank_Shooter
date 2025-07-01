#include "Tank.h"

Tank::Tank() {
    body.setSize(sf::Vector2f(40, 40));
    body.setFillColor(sf::Color::White);
    speed = 5.0f;
}

void Tank::draw(sf::RenderWindow& window) {
    window.draw(body);
}

sf::Vector2f Tank::getPosition() const {
    return body.getPosition();
}
