// Tank.h
#pragma once
#include <SFML/Graphics.hpp>

class Tank {
protected:
    sf::RectangleShape body;
    float speed;

public:
    Tank();
    virtual ~Tank() = default;

    virtual void move(float dx, float dy);
    virtual void update(float deltaTime) = 0; 
    virtual void draw(sf::RenderWindow& window);

    virtual void move(float dx, float dy) = 0;

    virtual void draw(sf::RenderWindow& window) const;

    sf::Vector2f getPosition() const;
};
