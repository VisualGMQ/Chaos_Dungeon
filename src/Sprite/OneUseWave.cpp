#include "Sprite/OneUseWave.hpp"

OneUseWave* OneUseWave::Create(){
    OneUseWave* wave = new OneUseWave;
    wave->Init();
    return wave;
}

OneUseWave::OneUseWave():isvalid(true){
    name = "OneUseWave";
    colliobj.SetColliType(WAVEABLE);
    colliobj.AttachColliType(DAMAGEABLE);
    prop.can_damage = true;
}

void OneUseWave::SetWaveColliCircle(Circle c){
    colliobj.Set(c);
}

/**
 * TRAP
 * 这里不知道为什么，在设置rect之后，碰撞引擎会改变其rect导致碰撞不精准。
 */
void OneUseWave::SetWaveColliRect(AABB rect){
    colliobj.Set(rect);
}

void OneUseWave::Init(){}

void OneUseWave::update(){
    DamageableSprite::update();
}

void OneUseWave::draw(){}

bool OneUseWave::IsValid() const{
    return isvalid;
}

void OneUseWave::InValid(){
    isvalid = false;
}
