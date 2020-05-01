#ifndef LITTLE_ROBO
#define LITTLE_ROBO
#include "Sprite.hpp"
#include "Drawable.hpp"
#include "Creature.hpp"
#include "ColliSystem.hpp"
#include "ColliAnimation.hpp"
#include "WorldModel.hpp"
#include "KilledEnemyNum.hpp"

class LittleRobo final : public Creature{
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
    void alive_logic() override;
    void die_logic() override;
    void draw() override;
    Drawable* draw_ptr;
    Animation ani_walk;
    ColliAnimation ani_attack;
    Texture tex_stand;
    State state;
    int die_count;
    FlipFlag hori_flag;
    int die_time_count;
    int oldhp;
};

#endif
