#include "Enemy.h"
#include <cstdlib>

Enemy::Enemy(float x, float y)
{
    body.setPosition(x, y);
    body.setSize(sf::Vector2f(40.f, 40.f));
    body.setFillColor(sf::Color::Red);
    speed = 50.f;
    timeSinceDirectionChange = 0.f;

    int dir = rand() % 4;
    if (dir == 0)
        direction = { 1.f, 0.f };
    else if (dir == 1)
        direction = { -1.f, 0.f };
    else if (dir == 2)
        direction = { 0.f, 1.f };
    else
        direction = { 0.f, -1.f };
}

void Enemy::update(float deltaTime)
{
    sf::Vector2f pos = body.getPosition();
    sf::Vector2f size = body.getSize();
    sf::Vector2f newPos = pos + direction * speed * deltaTime;

    if (newPos.x < 0 || newPos.x + size.x > 800)
        direction.x = -direction.x;
    if (newPos.y < 0 || newPos.y + size.y > 600)
        direction.y = -direction.y;

    body.move(direction * speed * deltaTime);
    timeSinceDirectionChange += deltaTime;

    if (timeSinceDirectionChange > 2.f)
    {
        int dir = rand() % 4;
        if (dir == 0)
            direction = { 1.f, 0.f };
        else if (dir == 1)
            direction = { -1.f, 0.f };
        else if (dir == 2)
            direction = { 0.f, 1.f };
        else
            direction = { 0.f, -1.f };
        timeSinceDirectionChange = 0.f;
    }

    // THAY ĐỔI: Nếu đang trúng đạn, sau 0.2s thì đánh dấu đã chết
    if (isHitEffect && hitClock.getElapsedTime().asSeconds() > 0.2f)
    {
        isDead = true;
    }
}

void Enemy::draw(sf::RenderWindow& window) const
{
    window.draw(body);
}

bool Enemy::isHit(const sf::FloatRect& bounds)
{
    if (!isHitEffect && body.getGlobalBounds().intersects(bounds)) // tránh bị trúng đạn 2 lần
    {
        body.setFillColor(sf::Color::White); // THAY ĐỔI: màu hiệu ứng
        isHitEffect = true;
        hitClock.restart();
        return true;
    }
    return false;
}

// THAY ĐỔI: Hàm mới
bool Enemy::shouldBeRemoved() const
{
    return isDead;
}

void Enemy::move(float dx, float dy)
{
    body.move(dx, dy);
}
