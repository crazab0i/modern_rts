#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(1400, 800), "My 2D Game");

    sf::CircleShape player(5);
    player.setFillColor(sf::Color::Green);
    player.setPosition(375, 275);

    sf::Vector2u windowSz = window.getSize();

    sf::Vector2i startMousePos;
    sf::Vector2i endMousePos;
    bool isDragging = false;

    using _key = sf::Keyboard;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // --- Player movement ---
        sf::Vector2f player_pos = player.getPosition();
        if ((_key::isKeyPressed(_key::Left) || _key::isKeyPressed(_key::A)) && player_pos.x > 0)
            player.move(-1, 0);
        if ((_key::isKeyPressed(_key::Right) || _key::isKeyPressed(_key::D)) && player_pos.x < windowSz.x)
            player.move(1, 0);
        if ((_key::isKeyPressed(_key::Up) || _key::isKeyPressed(_key::W)) && player_pos.y > 0)
            player.move(0, -1);
        if ((_key::isKeyPressed(_key::Down) || _key::isKeyPressed(_key::S)) && player_pos.y < windowSz.y)
            player.move(0, 1);

        // --- Mouse handling ---
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (!isDragging) {
                startMousePos = mousePos;
                isDragging = true;
            }
            endMousePos = mousePos;
        } else if (isDragging) {
            // Mouse released — stop dragging
            isDragging = false;
            // TODO: Handle selection box logic (e.g., select units inside)
        }

        // --- Drawing section ---
        window.clear();

        // Draw player
        window.draw(player);

        // Draw selection box if dragging
        if (isDragging) {
            float left   = std::min(startMousePos.x, endMousePos.x);
            float right  = std::max(startMousePos.x, endMousePos.x);
            float top    = std::min(startMousePos.y, endMousePos.y);
            float bottom = std::max(startMousePos.y, endMousePos.y);

            sf::Vertex lines[] = {
                sf::Vertex(sf::Vector2f(left, top)),
                sf::Vertex(sf::Vector2f(right, top)),

                sf::Vertex(sf::Vector2f(right, top)),
                sf::Vertex(sf::Vector2f(right, bottom)),

                sf::Vertex(sf::Vector2f(right, bottom)),
                sf::Vertex(sf::Vector2f(left, bottom)),

                sf::Vertex(sf::Vector2f(left, bottom)),
                sf::Vertex(sf::Vector2f(left, top)),
            };

            window.draw(lines, 8, sf::Lines);
        }

        window.display();
    }

    return 0;
}
