#ifndef LITTLE_ROBO
#define LITTLE_ROBO
#include "Sprite.hpp"
#include "DamageableSprite.hpp"
#include "ColliSystem.hpp"

class LittleRobo : public DamageableSprite{
    DEFINE_DELETEINTERFACE(LittleRobo)
    DEFINE_DELETEBODY(LittleRobo)
public:
    void Init() override;
    void EventHandle(SDL_Event& event) override;
    ~LittleRobo();
private:
    LittleRobo();
    void update() override;
    void draw() override;
    Drawable* draw_ptr;
    Animation ani_walk;
    Texture tex_stand;
    Texture tex_die;
};

#endif
