#ifndef LITTLE_ROBO
#define LITTLE_ROBO
#include "Sprite.hpp"
#include "DamageableSprite.hpp"

class LittleRobo : public DamageableSprite{
public:
    LittleRobo();
    void Init() override;
    void EventHandle(SDL_Event& event) override;
private:
    void update() override;
    void draw() override;
    Drawable* draw_ptr;
    Animation ani_walk;
    Texture tex_stand;
    Texture tex_die;
};

#endif
