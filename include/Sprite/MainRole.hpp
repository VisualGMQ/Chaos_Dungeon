#ifndef MAINROLE_HPP
#define MAINROLE_HPP
#include "Sprite.hpp"
#include "Collision.hpp"
#include "Creature.hpp"
#include "ColliSystem.hpp"
#include "Bullet.hpp"
#include "Animation.hpp"
#include "StaticTexture.hpp"
#include "HpBar.hpp"
#include "Bomb.hpp"
using namespace std;

/**
 * @brief 表示方向（八方向）的结构
 */
struct Direction{
    Direction();
    void Up();
    void Down();
    void Left();
    void Right();
    char vertical;  /** 竖直方向上的分量 */
    char horizontal;    /** 水平方向上的分量 */
};

class MainRole final : public Creature{
public:
    static MainRole* mainrole;
    enum State{
        NO_STATE = 0x00,
        INIT = 0x08,
        WALK = 0x01,
        STAND = 0x02,
        ATTACK = 0x04,
        DIE = 0x10
    };
    static MainRole* GetRole();
    void Init() override;
    void Collied(Object* oth, BasicProp* prop, const Manifold* m) override;
    ~MainRole();
protected:
    MainRole();
private:
    void shoot();
    void bomb();
    void alive_logic() override;
    void die_logic() override;
    void draw() override;
    void control();
    void update() override;
    void stand();
    void walk();
    Drawable* draw_ptr;
    Animation ani_walk;
    Animation ani_init;
    Texture tex_stand;
    int oldhp;
    State state;
    Vec aim_dir;    /** 从主角指向鼠标的向量 */
};

#endif
