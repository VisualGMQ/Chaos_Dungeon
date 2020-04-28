#ifndef DAMAGEABLE_HPP
#define DAMAGEABLE_HPP
#include "BasicProp.hpp"
#include "Sprite.hpp"

/**
 * @brief 可进行碰撞检测，并且可以进行伤害计算的精灵
 */
class DamageableSprite : public ColliableSprite{
public:
    BasicProp prop;
protected:
    DamageableSprite(){
        name = "DamageableSprite";
        colliobj.AttachColliType(ColliType::DAMAGEABLE);
    }
    void update() override{
        ColliableSprite::update();
        prop.can_damage = false;
    }
};

#endif
