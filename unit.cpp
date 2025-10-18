#include "entity.cpp"

class Unit : public Entity {
    private:
        int basic_attack_damage;
        int basic_attack_cd;
        int basic_attack_current_cd;
        int movespeed;
        int animation_time;
        Entity *target = nullptr;
        sf::Vector2f new_pos;
    public:
        void basic_attack() {
            target->modify_health(-basic_attack_damage);
        }
        void update() {
            //ai logic to establish target

            if (target) {
                if (basic_attack_current_cd == 0) {
                    basic_attack();
                    basic_attack_current_cd = basic_attack_cd;
                }
                basic_attack_current_cd--;
            }

        }

};