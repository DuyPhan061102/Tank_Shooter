// Game.cpp
#include "Game.h"
#include "Enemy.h"
#include <cstdlib>

Game::Game() : window(sf::VideoMode(800, 600), "Tank Battle"), isRunning(true)
{
    window.setFramerateLimit(60);
    if (!backgroundTexture.loadFromFile("assets/Images/background.jpg"))
    {

    }
    else
    {
        backgroundSprite.setTexture(backgroundTexture);
        backgroundSprite.setScale(
            window.getSize().x / backgroundSprite.getLocalBounds().width,
            window.getSize().y / backgroundSprite.getLocalBounds().height);

    }
    std::srand(static_cast<unsigned>(time(nullptr)));
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

    // -- BẮN ĐẠN nếu nhấn phím SPACE --
    static sf::Clock shootClock;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        if (shootClock.getElapsedTime().asMilliseconds() > 300)
        {
            sf::Vector2f startPos = player.getPosition();
            sf::Vector2f dir(1.f, 0.f); // Đạn bắn sang phải
            bullets.emplace_back(startPos, dir);
            shootClock.restart();
        }
    }

    // Sinh enemy mỗi 3s
    if (enemySpawnClock.getElapsedTime().asSeconds() > 3.f)
    {
        spawnEnemy();
        enemySpawnClock.restart();
    }

    // Cập nhật vị trí enemy
    for (auto& enemy : enemies)
    {
        enemy.update(dt);
    }

    // -- Cập nhật vị trí đạn --
    for (auto& bullet : bullets)
    {
        bullet.update(dt);
    }

    // -- Xoá đạn ra khỏi màn hình --
    bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
        [this](const Bullet& b)
        {
            return b.isOffScreen(window);
        }),
        bullets.end());

    // -- Va chạm giữa đạn và enemy --
    // THAY ĐỔI: không xóa enemy tại đây, để nó có thời gian hiện hiệu ứng
    for (auto b = bullets.begin(); b != bullets.end();)
    {
        bool bulletErased = false;
        for (auto& enemy : enemies)
        {
            if (enemy.isHit(b->getBounds()))
            {
                b = bullets.erase(b); // Xoá đạn
                bulletErased = true;
                break;
            }
        }
        if (!bulletErased)
            ++b;
    }

    // THAY ĐỔI: xoá enemy đã chết sau hiệu ứng
    enemies.erase(
        std::remove_if(enemies.begin(), enemies.end(),
            [](const Enemy& e) { return e.shouldBeRemoved(); }),
        enemies.end());
}

void Game::render()
{
    window.clear();
    window.draw(backgroundSprite);
    // Vẽ player
    player.draw(window);

    // -- Vẽ đạn --
    for (const auto& bullet : bullets)
    {
        bullet.draw(window);
    }

    // Vẽ enemy
    for (const auto& enemy : enemies)
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
