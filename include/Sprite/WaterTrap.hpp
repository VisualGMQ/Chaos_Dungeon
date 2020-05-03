#ifndef WATERTRAP_HPP
#define WATERTRAP_HPP
#include "Texture.hpp"
#include "Animation.hpp"
#include "GameObject.hpp"
#include "MainRole.hpp"

class WaterTrap : public GameObject{
public:
    static WaterTrap* Create();
private:
    WaterTrap();
    void update() override;
    void draw() override;
    void randDelayTime();
    void shoot();
    Animation ani;
    int count;
    int delay_shoot_time;
};

#endif
