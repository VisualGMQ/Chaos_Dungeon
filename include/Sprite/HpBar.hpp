#ifndef HPBAR_HPP
#define HPBAR_HPP
#include "GameObject.hpp"
#include "Texture.hpp"

class HpBar : public GameObject{
public:
    static HpBar* GetInstance();
    void SetHp(int hp);
private:
    void update() override;
    void draw() override;
    static HpBar* instance;
    HpBar();
    int hp;
    Texture tex_hp;
};

#endif
