#include "unit.hpp"
#include <cmath>

    void Unit::basic_attack() {
        target->modify_health(-basic_attack_damage);
    }
    void Unit::update() {
        //ai logic to establish target
        if (target) {
            if (basic_attack_current_cd == 0) {
                basic_attack();
                basic_attack_current_cd = basic_attack_cd;
            }
            basic_attack_current_cd--;
        }
        const float EPS = 0.1f;

        if (std::abs(new_pos.x - current_pos.x) > EPS ||
            std::abs(new_pos.y - current_pos.y) > EPS) {

            std::cout << "current pos: {" << current_pos.x << "," << current_pos.y
                    << "}\t new pos: {" << new_pos.x << "," << new_pos.y << "}\n";

            sf::Vector2f dir = new_pos - current_pos;
            float dist = std::sqrt(dir.x * dir.x + dir.y * dir.y);

            if (dist > 0) {
                dir /= dist; // normalize direction
                float step = std::min(dist, static_cast<float>(movespeed));
                current_pos += dir * step;
            }
        }
    }

    void Unit::setSelection(bool selection) {
        selected = selection;
    }

    std::pair<sf::Color, sf::Vector2f> Unit::render() {
        sf::Color color = sf::Color::Green;
        if (selected) {
            color = sf::Color::White;
        }
        return {color, current_pos};
    }

    void Unit::spawn(sf::Vector2f init_pos) {
        current_pos = init_pos;
        new_pos = init_pos;
    }

    sf::Vector2f Unit::getPosition() {
        return current_pos;
    }

    void Unit::updatePosition(sf::Vector2f target_pos) {
        if (selected) {
            std::cout << "setting\n";
            new_pos.x = target_pos.x;
            new_pos.y = target_pos.y;
        }
        std::cout << new_pos.x << " " << new_pos.y << std::endl;
    }

    void Unit::setMoveSpeed(float speed) {
        movespeed = speed;
    }
