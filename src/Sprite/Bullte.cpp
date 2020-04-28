#include "Sprite/Bullet.hpp"

Bullet* Bullet::Create(){
    auto* b = new Bullet;
    b->Init();
    return b;
}

Bullet::Bullet():isalive(true){
    name = "Bullet";
    colliobj.SetColliType(ColliType::BULLETABLE);
    colliobj.AttachLayer(ColliLayer::BULLET);
}

void Bullet::Init() {
    texture.Load("resources/bullet.png");
    texture.Scale(2, 2);
    colliobj.Set(Circle(0, 0, texture.Width()));
    prop.hp = 1;
    prop.damage = 1;
    ColliSystem::GetInstance()->AddDamageable(this);
}

void Bullet::SetShootVel(Vec pos, Vec vel){
    MoveTo(pos.x, pos.y);
    colliobj.physic_info.v = vel;
}

void Bullet::update() {
    DamageableSprite::update();
    colliobj.Update(1.0/Director::GetInstance()->fps);
    prop.can_damage = true;
    if(prop.hp<=0){
        isalive = false;
    }
    Camera* camera = Camera::GetInstance();
    
    //这里如果子弹超出了边界，那就自动销毁
    Vec pos = camera->GetPosition();
    int w = Director::GetInstance()->Width(),
        h = Director::GetInstance()->Height();
    const int offset = 100;
    if(Position().x<pos.x-offset ||
            Position().x>pos.x+w+offset||
            Position().y<pos.y-offset ||
            Position().y>pos.y+h+offset){
        isalive = false;
    }
    
    //子弹死亡的时候自动销毁
    if(!isalive){
        WorldModel::GetInstance()->DeleteElem(GetID());
    }
}

void Bullet::draw() {
    texture.Draw(Position().x, Position().y);
}

Bullet::~Bullet(){
    ColliSystem::GetInstance()->DeleteElem(GetID());
}
