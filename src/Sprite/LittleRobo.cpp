#include "Sprite/LittleRobo.hpp"

LittleRobo* LittleRobo::Create(){
    auto* robo = new LittleRobo;
    robo->Init();
    return robo;
}

LittleRobo::LittleRobo():draw_ptr(nullptr){
    name = "LittleRobo";
}

void LittleRobo::Init() {
    tex_stand.Load("resources/monster1_stand.png");
    tex_die.Load("resources/monster1_die.png");
    tex_die.Scale(3, 3);
    tex_stand.Scale(3, 3);
    TextureSheet ts("resources/monster1_walk.png", 2, 1);
    ani_walk.Load(ts, {5, 5});
    colliobj.Set(AABB(Position().x-tex_stand.Size().w/2, Position().y-tex_stand.Size().h/2, tex_stand.Width(), tex_stand.Height()));
    draw_ptr = &tex_stand;
    colliobj.AttachLayer(ColliLayer::ENEMY);
    prop.hp = 2;
    prop.damage = 1;
    ColliSystem::GetInstance()->AddDamageable(this);
}

void LittleRobo::update() {
    DamageableSprite::update();
    ani_walk.Update();
    colliobj.Update(1.0/Director::GetInstance()->fps);
}

void LittleRobo::draw() {
    draw_ptr->Draw(Position().x, Position().y);
}

LittleRobo::~LittleRobo(){
    ColliSystem::GetInstance()->DeleteElem(GetID());
}
