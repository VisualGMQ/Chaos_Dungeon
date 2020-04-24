#ifndef MAINROLE_HPP
#define MAINROLE_HPP
#include "Sprite.hpp"
#include "Collision.hpp"
#include "DamageableSprite.hpp"

class MainRole : public DamageableSprite{
public:
    enum State{
        NO_STATE = 0x00,
        WALK = 0x01,
        STAND = 0x02,
        ATTACK = 0x04
    };
    MainRole();
    void Init() override;
    void EventHandle(SDL_Event& event) override;
private:
    void draw() override;
    void update() override;
    void scale(float sx, float sy);
    Drawable* draw_ptr;
    Animation ani_walk;
    Texture tex_stand;
    State state;
};

#endif
