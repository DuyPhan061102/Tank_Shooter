// Game.h
#pragma once
#include <SFML/Graphics.hpp>
#include "PlayerTank.h"
#include "Tank.h"
#include "Enemy.h"
#include "Bullet.h"
#include <vector>

class Game
{
private:
    sf::RenderWindow window;
    sf::Clock clock;
    sf::Clock enemySpawnClock;

    bool isRunning;
    std::vector<Enemy> enemies;
    std::vector<Bullet> bullets;
    PlayerTank player;

    sf::Texture backgroundTexture;   // ảnh nền
    sf::Sprite backgroundSprite;     // sprite để vẽ ảnh

public:
    Game();
    void run();

private:
    void processEvents();
    void update(float dt);
    void render();
    void spawnEnemy();
};
