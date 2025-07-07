// PlayerTank.h
#pragma once
#include "Tank.h"

class PlayerTank : public Tank {
public:
    PlayerTank();

    void handleInput();
    void update(float deltaTime) override;
    void shoot(); 

private:
    sf::Vector2f movement;
};
