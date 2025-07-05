// Game.h
#pragma once
#include <SFML/Graphics.hpp>
#include "PlayerTank.h"

class Game {
private:
    sf::RenderWindow window;
    sf::Clock clock;
    bool isRunning;

    PlayerTank player;

public:
    Game();
    void run();

private:
    void processEvents();
    void update(float dt);
    void render();
};
