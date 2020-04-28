#include "Sprite/MainRole.hpp"

Direction::Direction():vertical(1),horizontal(0){}

void Direction::Up(){
    if(vertical!=1)
        vertical++;
}

void Direction::Down(){
    if(vertical!=-1)
        vertical--;
}

void Direction::Left(){
    if(horizontal!=-1)
        horizontal--;
}

void Direction::Right(){
    if(horizontal!=1)
        horizontal++;
}

MainRole* MainRole::Create(){
    auto* m = new MainRole;
    m->Init();
    return m;
}

MainRole::MainRole():state(MainRole::State::STAND),draw_ptr(&tex_stand){
    name = "MainRole";
}

void MainRole::Init() {
    tex_stand.Load("resources/mainrole_stand.png");
    tex_stand.Scale(3, 3);
    TextureSheet ts("resources/mainrole_walk.png", 2, 1);
    ani_walk.Load(ts, {4, 4});
    ani_walk.Scale(3, 3);
    colliobj.Set(AABB(Position().x-tex_stand.Width()/2, Position().y-tex_stand.Height()/2, tex_stand.Width(), tex_stand.Height()));
    colliobj.AttachColliType(ColliType::SOLIDABLE);
    colliobj.AttachLayer(ColliLayer::PLAYER);
    prop.hp = 3;
    prop.damage = 0;
    ColliSystem::GetInstance()->AddDamageable(this);
}

void MainRole::update() {
    DamageableSprite::update();
    Director* director = Director::GetInstance();
    aim_dir = Director::GetInstance()->GetMousePos()-Position();
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
    if(director->MouseButtonState(SDL_BUTTON_LEFT)==KeyState::PRESSED)
        shoot();
    colliobj.Update(1.0/Director::GetInstance()->fps);
    ani_walk.Update();
    if(prop.hp<=0)
        Hide();
}

void MainRole::shoot(){
    Bullet* b = Bullet::Create();
    b->GetColliObject().AttachLayer(ColliLayer::PLAYER);
    const int bullet_speed = 20;
    b->SetShootVel(Position(), Normalize(aim_dir)*bullet_speed);
    WorldModel::GetInstance()->AddGameObject(b);
}

void MainRole::draw() {
    draw_ptr->Draw(Position().x, Position().y);
}

MainRole::~MainRole(){
    ColliSystem::GetInstance()->DeleteElem(GetID());
}
