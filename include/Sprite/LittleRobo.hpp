#ifndef LITTLE_ROBO
#define LITTLE_ROBO
#include "Sprite.hpp"
#include "Drawable.hpp"
#include "DamageableSprite.hpp"
#include "ColliSystem.hpp"
#include "Animation.hpp"
#include "WorldModel.hpp"

class LittleRobo final : public DamageableSprite{
public:
    enum State{
        STAND,
        ATTACK,
        DIE,
        WALK
    };
    static LittleRobo* Create();
    void Init() override;
    void Stand();
    void Attack();
    void Die();
    void Walk(Vec vel);
    ~LittleRobo();
private:
    LittleRobo();
    void update() override;
    void draw() override;
    Drawable* draw_ptr;
    Animation ani_walk;
    Animation ani_attack;
    Texture tex_stand;
    Texture tex_die;
    State state;
    int die_count;
    FlipFlag hori_flag;
};

#endif
