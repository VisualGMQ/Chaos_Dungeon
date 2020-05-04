#ifndef BULLET_HPP
#define BULLET_HPP
#include "DamageableSprite.hpp"
#include "WorldModel.hpp"
#include "Camera.hpp"
#include "OneUseAnimation.hpp"
#include "MusicRepo.hpp"

class Bullet final : public DamageableSprite{
public:
    static Bullet* Create();
    void Init() override;
    void SetShootVel(Vec pos, Vec vel);
    ~Bullet();
private:
    Bullet();
    bool isalive;
    void update() override;
    void draw() override;
    Texture texture;
};

#endif
