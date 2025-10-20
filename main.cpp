#include "unit.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(1400, 800), "Test");

    Unit soldier;
    soldier.spawn({375, 275});
    sf::CircleShape soldier_s(5);
    soldier_s.setFillColor(sf::Color::Green);
    soldier_s.setPosition({375, 275});
    soldier.setMoveSpeed(.05);

    sf::Vector2i startMousePos;
    sf::Vector2i endMousePos;
    sf::Vector2f target_pos;
    bool isDragging = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Right) {
                    target_pos = window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
                    std::cout << "window pos " << target_pos.x << " " << target_pos.y << std::endl;
                    soldier.updatePosition(target_pos);
                } else if (event.mouseButton.button == sf::Mouse::Left) {
                    soldier.setSelection(false);
                }
            }
            
        }

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

            sf::Vector2f soldier_pos = soldier.getPosition();
            int greater_x = std::max(startMousePos.x, endMousePos.x);
            int lower_x   = std::min(startMousePos.x, endMousePos.x);
            int greater_y = std::max(startMousePos.y, endMousePos.y);
            int lower_y   = std::min(startMousePos.y, endMousePos.y);

            if ((soldier_pos.x <= greater_x && soldier_pos.x >= lower_x) &&
                (soldier_pos.y <= greater_y && soldier_pos.y >= lower_y)) {
                std::cout << "setting selection\n";
                soldier.setSelection(true);
            }
        }

        std::pair<sf::Color, sf::Vector2f> render_obj = soldier.render();
        soldier_s.setPosition(render_obj.second);
        soldier_s.setFillColor(render_obj.first);
        soldier.update();

        // --- Drawing section ---
        window.clear();

        // Draw soldier
        window.draw(soldier_s);

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
}
