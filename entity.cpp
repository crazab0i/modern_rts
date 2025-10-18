#pragma once
#include <SFML/System/Vector2.hpp>
#include "enums.cpp"


class Entity {
    private:
        players player_owner;
        bool selected = false;
        bool visual_update = false;
        int health;
    
        sf::Vector2f pos;
    public:
        virtual void update() = 0;
        virtual void draw(float df) = 0;
        virtual sf::Vector2f getPosition() = 0;
        virtual ~Entity() = default;
        void modify_health(int health_diff) {
            health += health_diff;
        }
};