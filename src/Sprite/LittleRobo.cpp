#include "Sprite/LittleRobo.hpp"

list<LittleRobo*> LittleRobo::instances;
list<unsigned int> LittleRobo::willdel_list;

LittleRobo::LittleRobo():draw_ptr(nullptr){}

void LittleRobo::Init() {
    tex_stand.Load("resources/monster1_stand.png");
    tex_die.Load("resources/monster1_die.png");
    tex_die.Scale(5, 5);
    tex_stand.Scale(5, 5);
    TextureSheet ts("resources/monster1_walk.png", 2, 1);
    ani_walk.Load(ts, {5, 5});
    colliobj.Set(AABB(Position().x-tex_stand.Size().w/2, Position().y-tex_stand.Size().h/2, tex_stand.Width(), tex_stand.Height()));
    draw_ptr = &tex_stand;
    colliobj.AttachLayer(ColliLayer::ENEMY);
    prop.hp = 2;
    prop.damage = 1;
    ColliSystem::GetInstance()->AddDamageable(this);
}

void LittleRobo::EventHandle(SDL_Event& event) {}

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
