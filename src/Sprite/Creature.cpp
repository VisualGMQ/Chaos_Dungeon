#include "Sprite/Creature.hpp"

Creature::Creature(){
    name = "Creature";
}

void Creature::update() {
    DamageableSprite::update();
    if(prop.hp>0)
        alive_logic();
    if(prop.hp<=0)
        die_logic();
}
