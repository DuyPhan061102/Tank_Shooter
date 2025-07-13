#ifndef ENEMY_H
#define ENEMY_H

#include "Tank.h"
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class Enemy : public Tank
{
public:
    Enemy(float x, float y);
    void move(float dx, float dy) override;
    void update(float deltaTime) override;
    void draw(sf::RenderWindow &window) const override;

    bool isHit(const sf::FloatRect &bounds);
    void markToRemove();
    bool shouldBeRemoved() const;

private:
    sf::Vector2f direction;
    float timeSinceDirectionChange;

    // 🔻 Cần thêm cho hiệu ứng trúng đạn:
    bool isHitEffect = false;
    sf::Clock hitClock;
    bool toBeRemoved = false;
};

#endif
