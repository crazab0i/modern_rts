#pragma once
#include <SFML/Graphics.hpp>
#include "enums.hpp"
#include <iostream>

class Entity {
    private:
        players player_owner;
        bool selected = false;
        bool visual_update = false;
        int health;
    
        sf::Vector2f pos;
    public:
        virtual void update() = 0;
        virtual sf::Vector2f getPosition() = 0;
        virtual ~Entity() = default;
        void modify_health(int health_diff) {
            health += health_diff;
        }
        virtual std::pair<sf::Color, sf::Vector2f> render() = 0;
};