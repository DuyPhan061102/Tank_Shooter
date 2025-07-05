#include <SFML/Graphics.hpp>
#include "Enemy.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Tank Battle Test");

    sf::Clock clock;
    Enemy enemy(100.f, 100.f);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float deltaTime = clock.restart().asSeconds();
        enemy.update(deltaTime);

        window.clear();
        enemy.draw(window);  // kế thừa từ Tank
        window.display();
    }

    return 0;
}