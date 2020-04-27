#ifndef MAINROLE_HPP
#define MAINROLE_HPP
#include "Sprite.hpp"
#include "Collision.hpp"
#include "DamageableSprite.hpp"
#include "ColliSystem.hpp"
#include "Bullet.hpp"
using namespace std;

class MainRole : public DamageableSprite{
    DEFINE_DELETEINTERFACE(MainRole)
    DEFINE_DELETEBODY(MainRole)
public:
    enum State{
        NO_STATE = 0x00,
        WALK = 0x01,
        STAND = 0x02,
        ATTACK = 0x04
    };
    void Init() override;
    void EventHandle(SDL_Event& event) override;
    void Shoot(Vec dir);
    ~MainRole();
protected:
    MainRole();
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
