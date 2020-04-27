#include "Sprite/MainRole.hpp"

list<MainRole*> MainRole::instances;
list<unsigned int> MainRole::willdel_list;

MainRole::MainRole():state(MainRole::State::STAND),draw_ptr(&tex_stand){
}

void MainRole::Init() {
    tex_stand.Load("resources/mainrole_stand.png");
    tex_stand.Scale(5, 5);
    TextureSheet ts("resources/mainrole_walk.png", 2, 1);
    ani_walk.Load(ts, {4, 4});
    ani_walk.Scale(5, 5);
    colliobj.Set(AABB(Position().x-tex_stand.Width()/2, Position().y-tex_stand.Height()/2, tex_stand.Width(), tex_stand.Height()));
    colliobj.AttachColliType(ColliType::SOLIDABLE);
    colliobj.AttachLayer(ColliLayer::PLAYER);
    prop.hp = 3;
    prop.damage = 0;
    Shoot(Vec(5, 5));
    ColliSystem::GetInstance()->AddDamageable(this);
}

void MainRole::Shoot(Vec dir){
    Bullet* b = Bullet::Create();
    b->prop.damage = 1;
    b->SetShootVel(Vec(100, 100), dir);
    b->Show();
    b->GetColliObject().AttachLayer(ColliLayer::PLAYER);
    WorldModel::GetInstance()->AddDmgable(b);
}

void MainRole::EventHandle(SDL_Event& event) {}

void MainRole::update() {
    DamageableSprite::update();
    Director* director = Director::GetInstance();
    const float speed = 10;
    colliobj.physic_info.v.Set(0, 0);
    SET_STATE(state, State::STAND);
    if(director->KeyState(SDLK_w)==KeyState::PRESSING){
        colliobj.physic_info.v.y = speed;
        SET_STATE(state, State::WALK);
    }
    if(director->KeyState(SDLK_a)==KeyState::PRESSING){
        colliobj.physic_info.v.x = -speed;
        SET_STATE(state, State::WALK);
    }
    if(director->KeyState(SDLK_s)==KeyState::PRESSING){
        colliobj.physic_info.v.y = -speed;
        SET_STATE(state, State::WALK);
    }
    if(director->KeyState(SDLK_d)==KeyState::PRESSING){
        colliobj.physic_info.v.x = speed;
        SET_STATE(state, State::WALK);
    }
    if(HAS_STATE(state, State::WALK)){
        ani_walk.Play();
        draw_ptr = &ani_walk;
    }else{
        colliobj.physic_info.v.Set(0, 0);
        ani_walk.Stop();
        draw_ptr = &tex_stand;
    }       
    colliobj.Update(1.0/Director::GetInstance()->fps);
    ani_walk.Update();
}

void MainRole::draw() {
    draw_ptr->Draw(Position().x, Position().y);
}

MainRole::~MainRole(){
    ColliSystem::GetInstance()->DeleteElem(GetID());
}
