// Game.cpp
#include "Game.h"
#include "Enemy.h"
#include <cstdlib> 

Game::Game() : window(sf::VideoMode(800, 600), "Tank Battle"), isRunning(true) {
    window.setFramerateLimit(60);
    std::srand(static_cast<unsigned>(time(nullptr)));
}

void Game::run() {
    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();
        processEvents();
        update(dt);
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void Game::update(float dt) {
    // Cập nhật player
    player.update(dt);

    // Sinh enemy mỗi 3s
    if (enemySpawnClock.getElapsedTime().asSeconds() > 3.f) {
        spawnEnemy();
        enemySpawnClock.restart();
    }

    // Cập nhật vị trí enemy
    for (auto& enemy : enemies) {
        enemy.update(dt);
    }
}

void Game::render() {
    window.clear();

    // Vẽ player
    player.draw(window);

    // Vẽ enemy
    for (const auto& enemy : enemies) {
        enemy.draw(window);
    }

    window.display();
}

void Game::spawnEnemy() {
    float x = static_cast<float>(rand() % 700 + 50);
    float y = static_cast<float>(rand() % 500 + 50);
    enemies.emplace_back(x, y);
}
