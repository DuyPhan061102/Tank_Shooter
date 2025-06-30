#include <SFML/Graphics.hpp>

int main() {
    // Tạo cửa sổ game 800x600 có tiêu đề
    sf::RenderWindow window(sf::VideoMode(800, 600), "Tank Battle - Test");

    // Giới hạn tốc độ khung hình
    window.setFramerateLimit(60);

    // Tạo hình chữ nhật đại diện cho tank (chỉ để test)
    sf::RectangleShape tank(sf::Vector2f(60, 30));
    tank.setFillColor(sf::Color::Green);
    tank.setPosition(370, 285); // Chính giữa

    // Vòng lặp chính của game
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // Đóng cửa sổ khi nhấn nút X hoặc ESC
            if (event.type == sf::Event::Closed || 
               (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                window.close();
            }
        }

        // Di chuyển tank bằng phím mũi tên
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            tank.move(-5.f, 0.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            tank.move(5.f, 0.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            tank.move(0.f, -5.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            tank.move(0.f, 5.f);
        }

        // Vẽ mọi thứ
        window.clear(sf::Color::Black);  // Clear màn hình màu đen
        window.draw(tank);               // Vẽ "tank"
        window.display();                // Hiển thị lên cửa sổ
    }

    return 0;
}
