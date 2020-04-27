#ifndef BULLET_HPP
#define BULLET_HPP
#include "Sprite/DamageableSprite.hpp"
#include "WorldModel.hpp"

class Bullet : public DamageableSprite{
    DEFINE_DELETEINTERFACE(Bullet)
    DEFINE_DELETEBODY(Bullet)
public:
    void Init() override;
    void EventHandle(SDL_Event& event) override;
    void SetShootVel(Vec pos, Vec vel);
private:
    Bullet();
    bool isalive;
    void update() override;
    void draw() override;
    Texture texture;
};

#endif
