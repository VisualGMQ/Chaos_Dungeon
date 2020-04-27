#include "Sprite/Bullet.hpp"

list<Bullet*> Bullet::instances;
list<unsigned int> Bullet::willdel_list;

Bullet::Bullet():isalive(true){
    colliobj.SetColliType(ColliType::BULLETABLE);
    colliobj.AttachLayer(ColliLayer::BULLET);
}

void Bullet::Init() {
    texture.Load("resources/bullet.png");
    texture.Scale(2, 2);
    colliobj.Set(Circle(0, 0, texture.Width()));
    prop.hp = 1;
    ColliSystem::GetInstance()->AddDamageable(this);
}

void Bullet::SetShootVel(Vec pos, Vec vel){
    MoveTo(pos.x, pos.y);
    colliobj.physic_info.v = vel;
}

void Bullet::EventHandle(SDL_Event& event) {}

void Bullet::update() {
    DamageableSprite::update();
    colliobj.Update(1.0/Director::GetInstance()->fps);
    if(prop.hp<=0){
        isalive = false;
    }
    if(!isalive){
        WorldModel::GetInstance()->DeleteElem(GetID());
    }
}

void Bullet::draw() {
    texture.Draw(Position().x, Position().y);
}
