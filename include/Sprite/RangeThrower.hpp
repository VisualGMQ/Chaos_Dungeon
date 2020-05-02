#ifndef RANGETHROWER_HPP
#define RANGETHROWER_HPP
#include "Creature.hpp"
#include "Animation.hpp"
#include "Texture.hpp"
#include "Drawable.hpp"
#include "MainRole.hpp"
#include <random>
#include <ctime>

class Boomerange : public DamageableSprite{
public:
    static const int speed = 5;
    static Boomerange* Create();
    void Init() override;
    void UpdateOrgPos(Vec pos); /** 更新要返回的目的地 */
    void Shoot(Vec dir);
private:
    Boomerange();
    void update() override;
    void draw() override;
    Texture tex;
    Vec shootDir;
    Vec orgpos;
    float angle;
    bool isshooted;
};

class RangeThrower : public Creature{
public:
    enum class State{
        STAND,
        THROW,
        WALK,
        DIE
    };
    static RangeThrower* Create();
    void Init() override;
private:
    RangeThrower();
    void update() override;
    void alive_logic() override;
    void die_logic() override;
    void draw() override;
    void stand();
    void walk();
    void throw_range();
    void approchMainrole();
    void rand_throw_time();
    Texture tex_stand;
    Animation ani_walk;
    Animation ani_throw;
    Texture tex_boomerange;
    State state;
    Drawable* draw_ptr;
    bool has_boomerange;    /** 判断回旋镖是否丢出手了 */
    FlipFlag fflag;
    int time_count;
    int throw_delay_time;   /** 回旋镖回来之后距离下一次扔回旋镖的事件 */
    Boomerange* br;
};

#endif
