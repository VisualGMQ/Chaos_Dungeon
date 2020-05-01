#include "Sprite/HpBar.hpp"

HpBar* HpBar::instance = nullptr;

HpBar::HpBar():tex_hp("resources/life.png"),hp(0){
    tex_hp.Scale(3, 3);
}

HpBar* HpBar::GetInstance(){
    if(instance==nullptr)
        instance = new HpBar;
    return instance;
}

void HpBar::SetHp(int hp){
    this->hp = hp;
}

void HpBar::update() {}

void HpBar::draw(){
    const int padding = tex_hp.Width()/3;
    for(int i=0;i<hp;i++)
        tex_hp.Draw(Position().x+(tex_hp.Width()+padding)*i, Position().y);
}

