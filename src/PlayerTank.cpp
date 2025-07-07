// PlayerTank.cpp
#include "PlayerTank.h"
#include <SFML/Window/Keyboard.hpp>

PlayerTank::PlayerTank()
{
    speed = 200.f;
    body.setFillColor(sf::Color::Green);
}

void PlayerTank::handleInput()
{
    movement = {0.f, 0.f};

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        movement.y -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        movement.y += 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        movement.x -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        movement.x += 1.f;
}
void PlayerTank::draw(sf::RenderWindow &window) const
{
    window.draw(body); // Hoặc bất kỳ logic custom nào bạn muốn
}
void PlayerTank::update(float deltaTime)
{
    handleInput();
    move(movement.x * speed * deltaTime, movement.y * speed * deltaTime);
}
void PlayerTank::move(float dx, float dy)
{
    body.move(dx, dy);
}
void PlayerTank::shoot()
{
}
