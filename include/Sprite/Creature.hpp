#ifndef CREATURE_HPP
#define CREATURE_HPP
#include "DamageableSprite.hpp"

class Creature : public DamageableSprite{
protected:
    Creature();
    void update() override;
    virtual void alive_logic() = 0; /** 人物还活着的时候的逻辑 */
    virtual void die_logic() = 0;   /** 人物凉凉后的逻辑，可以在这里播放一些死亡动画之类的 */
};

#endif
