#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Tank.h"
#include "Enemy.h"     
#include <vector>

class Game {
private:
    sf::RenderWindow window;
    sf::Clock clock;
    sf::Clock enemySpawnClock;
    bool isRunning;
    std::vector<Enemy> enemies;
public:
    Game();
    void run();

private:
    void processEvents();
    void update(float dt);
    void render();
    void spawnEnemy();
};

#endif