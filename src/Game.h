#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Tank.h"
#include <vector>

class Game {
private:
    sf::RenderWindow window;
    sf::Clock clock;
    bool isRunning;

public:
    Game();
    void run();

private:
    void processEvents();
    void update(float dt);
    void render();
};

#endif