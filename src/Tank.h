
#ifndef TANK_H
#define TANK_H

#include <SFML/Graphics.hpp>

class Tank {
protected:
    sf::RectangleShape body;
    float speed;

public:
    Tank();
    virtual void move(float dx, float dy) = 0;
    virtual void draw(sf::RenderWindow& window) const;
    sf::Vector2f getPosition() const;
};

#endif