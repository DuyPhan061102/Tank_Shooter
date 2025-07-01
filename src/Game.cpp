#include "Game.h"

Game::Game() : window(sf::VideoMode(800, 600), "Tank Battle"), isRunning(true) {
    window.setFramerateLimit(60);
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
    // TODO: Update player, bullets, enemies, etc.
}

void Game::render() {
    window.clear();
    // TODO: Draw game objects
    window.display();
}