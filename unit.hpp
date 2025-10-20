#include "entity.hpp"

class Unit : public Entity {
    private:
        int basic_attack_damage;
        int basic_attack_cd;
        int basic_attack_current_cd;
        float movespeed;
        int animation_time;
        bool selected = false;
        Entity *target = nullptr;
        sf::Vector2f new_pos;
        sf::Vector2f current_pos;
    public:
        void basic_attack();
        void update();
        void setSelection(bool selection);
        std::pair<sf::Color, sf::Vector2f> render();
        void spawn(sf::Vector2f init_pos);
        sf::Vector2f getPosition();
        void updatePosition(sf::Vector2f target_pos);
        void setMoveSpeed(float speed);
};