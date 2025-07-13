// Game.cpp
#include <iostream> 
#include "Game.h"
#include "Enemy.h"
#include <cstdlib>

Game::Game() : window(sf::VideoMode(800, 600), "Tank Battle"), isRunning(true)
{
    window.setFramerateLimit(60);
    std::srand(static_cast<unsigned>(time(nullptr)));

    // Tải âm thanh bắn
    if (!shootBuffer.loadFromFile("assets/Sounds/shoot.wav"))
    {
        std::cout << "❌ Không thể tải file shoot.wav\n";
    }
    else
    {
        shootSound.setBuffer(shootBuffer);
        shootSound.setVolume(100.f); // âm lượng tối đa
    }

    // Tải âm thanh nổ
    if (!explosionBuffer.loadFromFile("assets/Sounds/explosion.wav"))
    {
        std::cout << "❌ Không thể tải file explosion.wav\n";
    }
    else
    {
        explosionSound.setBuffer(explosionBuffer);
        explosionSound.setVolume(100.f); // âm lượng tối đa
    }
}

void Game::run()
{
    while (window.isOpen())
    {
        float dt = clock.restart().asSeconds();
        processEvents();
        update(dt);
        render();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void Game::update(float dt)
{
    // Cập nhật player
    player.update(dt);
    // -- BẮN ĐẠN nếu nhấn phím SPACE --////////////////////
    static sf::Clock shootClock;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        if (shootClock.getElapsedTime().asMilliseconds() > 300)
        {
            sf::Vector2f startPos = player.getPosition();
            sf::Vector2f dir(1.f, 0.f); // Đạn bắn sang phải
            bullets.emplace_back(startPos, dir);
            shootSound.play();
            shootClock.restart();
        }
    }
    //////////////////////////////////////
    // Sinh enemy mỗi 3s
    if (enemySpawnClock.getElapsedTime().asSeconds() > 3.f)
    {
        spawnEnemy();
        enemySpawnClock.restart();
    }

    // Cập nhật vị trí enemy
    for (auto &enemy : enemies)
    {
        enemy.update(dt);
    }
    ////////////////////
    // -- Cập nhật vị trí đạn --
    for (auto &bullet : bullets)
    {
        bullet.update(dt);
    }

    // -- Xoá đạn ra khỏi màn hình --
    bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
                                 [this](const Bullet &b)
                                 {
                                     return b.isOffScreen(window);
                                 }),
                  bullets.end());
    ///////////////////////////
    // -- Va chạm giữa đạn và enemy --
    for (auto b = bullets.begin(); b != bullets.end();)
    {
        bool bulletErased = false;
        for (auto e = enemies.begin(); e != enemies.end();)
        {
            if (e->isHit(b->getBounds()))
            {
                // Nếu va chạm, phát âm thanh nổ và xoá enemy và đạn
                explosionSound.play();
                e = enemies.erase(e);
                b = bullets.erase(b);
                bulletErased = true;
                break;
            }
            else
            {
                ++e;
            }
        }
        if (!bulletErased)
            ++b;
    }
    ////////////////////
}

void Game::render()
{
    window.clear();

    // Vẽ player
    player.draw(window);
    // -- Vẽ đạn --
    for (const auto &bullet : bullets)
    {
        bullet.draw(window);
    }
    ////////////////////
    // Vẽ enemy
    for (const auto &enemy : enemies)
    {
        enemy.draw(window);
    }

    window.display();
}

void Game::spawnEnemy()
{
    float x = static_cast<float>(rand() % 700 + 50);
    float y = static_cast<float>(rand() % 500 + 50);
    enemies.emplace_back(x, y);
}
