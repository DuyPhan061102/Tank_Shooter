#include <iostream> 
#include "Game.h"
#include "Enemy.h"
#include <cstdlib>

Game::Game() : window(sf::VideoMode(800, 600), "Tank Battle"), isRunning(true)
{
    window.setFramerateLimit(60);
    score = 0;

    if (!font.loadFromFile("assets/arial.ttf")) {
        // Nếu cần xử lý lỗi thì thêm vào đây
    }

    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10.f, 10.f);
    scoreText.setString("Score: 0");

    std::srand(static_cast<unsigned>(time(nullptr)));

    // Tải font
    if (!font.loadFromFile("assets/Fonts/arial.ttf")) {
        std::cout << "❌ Không thể tải font arial.ttf\n";
    }

    gameOverText.setFont(font);
    gameOverText.setString("GAME OVER");
    gameOverText.setCharacterSize(48);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setPosition(250.f, 250.f);

    // Tải âm thanh bắn
    if (!shootBuffer.loadFromFile("assets/Sounds/shoot.wav")) {
        std::cout << "❌ Không thể tải file shoot.wav\n";
    } else {
        shootSound.setBuffer(shootBuffer);
        shootSound.setVolume(100.f);
    }

    // Tải âm thanh nổ
    if (!explosionBuffer.loadFromFile("assets/Sounds/explosion.wav")) {
        std::cout << "❌ Không thể tải file explosion.wav\n";
    } else {
        explosionSound.setBuffer(explosionBuffer);
        explosionSound.setVolume(100.f);
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
    if (!isRunning) return;

    player.update(dt);

    static sf::Clock shootClock;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        if (shootClock.getElapsedTime().asMilliseconds() > 300)
        {
            sf::Vector2f startPos = player.getPosition();
            sf::Vector2f dir(1.f, 0.f);
            bullets.emplace_back(startPos, dir);
            shootSound.play();
            shootClock.restart();
        }
    }

    if (enemySpawnClock.getElapsedTime().asSeconds() > 3.f)
    {
        spawnEnemy();
        enemySpawnClock.restart();
    }

    for (auto& enemy : enemies)
    {
        enemy.update(dt);
    }

    for (auto& bullet : bullets)
    {
        bullet.update(dt);
    }

    bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
        [this](const Bullet& b)
        {
            return b.isOffScreen(window);
        }), bullets.end());

    for (auto b = bullets.begin(); b != bullets.end();)
    {
        bool bulletErased = false;
        for (auto e = enemies.begin(); e != enemies.end();)
        {
            if (e->isHit(b->getBounds()))
            {
                explosionSound.play();
                e = enemies.erase(e);
                b = bullets.erase(b);
                bulletErased = true;
                score += 100;
                scoreText.setString("Score: " + std::to_string(score));
                break;
            }
            else {
                ++e;
            }
        }
        if (!bulletErased)
            ++b;
    }

    sf::FloatRect playerBounds(player.getPosition().x, player.getPosition().y, 40.f, 40.f);
    for (auto& enemy : enemies)
    {
        if (enemy.isHit(playerBounds))
        {
            isRunning = false;
            break;
        }
    }
}

void Game::render()
{
    window.clear();

    player.draw(window);

    for (const auto& bullet : bullets)
    {
        bullet.draw(window);
    }

    for (const auto& enemy : enemies)
    {
        enemy.draw(window);
    }
    window.draw(scoreText);

    if (!isRunning)
    {
        window.draw(gameOverText);
    }

    window.display();
}

void Game::spawnEnemy()
{
    float x = static_cast<float>(rand() % 700 + 50);
    float y = static_cast<float>(rand() % 500 + 50);
    enemies.emplace_back(x, y);
}
