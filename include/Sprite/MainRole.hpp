#ifndef MAINROLE_HPP
#define MAINROLE_HPP
#include "Sprite.hpp"
#include "Collision.hpp"
#include "DamageableSprite.hpp"
#include "ColliSystem.hpp"
#include "Bullet.hpp"
#include "Animation.hpp"
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

class MainRole final : public DamageableSprite{
public:
    static MainRole* Create();
    enum State{
        NO_STATE = 0x00,
        WALK = 0x01,
        STAND = 0x02,
        ATTACK = 0x04
    };
    void Init() override;
    ~MainRole();
protected:
    MainRole();
private:
    void shoot();
    void draw() override;
    void update() override;
    Drawable* draw_ptr;
    Animation ani_walk;
    Texture tex_stand;
    State state;
    Vec aim_dir;    /** 从主角指向鼠标的向量 */
};

#endif
