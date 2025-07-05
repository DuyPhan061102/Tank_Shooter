#include "Enemy.h"
#include <cstdlib>

Enemy::Enemy(float x, float y) {
    body.setPosition(x, y);
    body.setSize(sf::Vector2f(40.f, 40.f));
    body.setFillColor(sf::Color::Red);
    speed = 50.f;
    timeSinceDirectionChange = 0.f;

    int dir = rand() % 4;
    if (dir == 0) direction = {1.f, 0.f};
    else if (dir == 1) direction = {-1.f, 0.f};
    else if (dir == 2) direction = {0.f, 1.f};
    else direction = {0.f, -1.f};
}

void Enemy::update(float deltaTime) {
    body.move(direction * speed * deltaTime);
    timeSinceDirectionChange += deltaTime;

    if (timeSinceDirectionChange > 2.f) {
        int dir = rand() % 4;
        if (dir == 0) direction = {1.f, 0.f};
        else if (dir == 1) direction = {-1.f, 0.f};
        else if (dir == 2) direction = {0.f, 1.f};
        else direction = {0.f, -1.f};
        timeSinceDirectionChange = 0.f;
    }
}

bool Enemy::isHit(const sf::FloatRect& bounds) {
    return body.getGlobalBounds().intersects(bounds);
}

void Enemy::move(float dx, float dy) {
    body.move(dx, dy);
}
