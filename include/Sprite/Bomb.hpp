#ifndef BOMB_HPP
#define BOMB_HPP
#include "Sprite/Sprite.hpp"
#include "Drawable.hpp"
#include "WorldModel.hpp"

class Bomb : public ColliableSprite{
public:
    enum class State{
        SIMPLE,
        FIRING,
        BOMB
    };
    void Init() override;
    static Bomb* Create();
    void Fire();    /** 点燃炸弹 */
private:
    Bomb();
    void update() override;
    void draw() override;
    Texture tex;
    Animation ani_fire;
    Drawable* draw_ptr;
    State state;
    int fire_time;
    int time_count;
};

#endif
