#ifndef LITTLE_ROBO
#define LITTLE_ROBO
#include "Sprite.hpp"
#include "Drawable.hpp"
#include "DamageableSprite.hpp"
#include "ColliSystem.hpp"
#include "Animation.hpp"

class LittleRobo final : public DamageableSprite{
public:
    static LittleRobo* Create();
    void Init() override;
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
