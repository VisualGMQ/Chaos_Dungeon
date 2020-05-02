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

MainRole* MainRole::mainrole = nullptr;

MainRole* MainRole::GetRole(){
    if(mainrole==nullptr){
        mainrole = new MainRole;
        mainrole->Init();
    }
    return mainrole;
}

MainRole::MainRole():state(MainRole::State::INIT),draw_ptr(&tex_stand),oldhp(0){
    name = "MainRole";
    tex_stand.Load("resources/mainrole_stand.png");
    tex_stand.Scale(3, 3);
    TextureSheet ts("resources/mainrole_walk.png", 2, 1);
    ani_walk.Load(ts, {4, 4});
    ani_walk.Scale(3, 3);
    ani_walk.EnableLoop();
    TextureSheet ts2("resources/mainrole_init.png", 4, 1);
    ts2.Scale(3, 3);
    ani_init.Load(ts2, {3, 3, 5, 5});
    colliobj.Set(AABB(Position().x-tex_stand.Width()/2, Position().y-tex_stand.Height()/2, tex_stand.Width(), tex_stand.Height()));
    colliobj.AttachColliType(ColliType::SOLIDABLE);
    colliobj.AttachLayer(ColliLayer::PLAYER);
}

void MainRole::Init() {
    prop.hp = 3;
    prop.damage = 0;
    ColliSystem::GetInstance()->AddDamageable(this);
    ani_init.Play();
    ani_init.Pause();
}

void MainRole::update() {
    Creature::update();
    if(oldhp>prop.hp){
        TextureSheet ts("resources/buster2.png", 5, 1);
        ts.Scale(3, 3);
        OneUseAnimation* ani = OneUseAnimation::Create();
        ani->Load(ts, {1, 1, 1, 1, 1});
        ani->MoveTo(Position().x, Position().y);
        WorldModel::GetInstance()->AddGameObject("effect", ani);
    }
    HpBar::GetInstance()->SetHp(prop.hp);
    oldhp = prop.hp;
}

void MainRole::shoot(){
    Bullet* b = Bullet::Create();
    b->GetColliObject().AttachLayer(ColliLayer::PLAYER);
    const int bullet_speed = 20;
    b->SetShootVel(Position(), Normalize(aim_dir)*bullet_speed);
    WorldModel::GetInstance()->AddGameObject("bullet", b);
}

void MainRole::bomb(){
    Bomb* bomb = Bomb::Create();
    bomb->MoveTo(Position().x, Position().y);
    bomb->Fire();
    WorldModel::GetInstance()->AddGameObject("item", bomb);
}

void MainRole::Collied(Object* oth, BasicProp* prop, const Manifold* m){
    if(HAS_STATE(oth->GetColliType(), ColliType::BULLETABLE)){
        TextureSheet ts("resources/buster2.png", 5, 1);
        ts.Scale(3, 3);
        OneUseAnimation* ani = OneUseAnimation::Create();
        ani->Load(ts, {1, 1, 1, 1, 1});
        ani->MoveTo(Position().x, Position().y);
        WorldModel::GetInstance()->AddGameObject("effect", ani);
    }
}

void MainRole::alive_logic() {
    colliobj.physic_info.v.Set(0, 0);
    if(!HAS_STATE(state, INIT) && prop.hp>0){
        control(); 
    }
    if(HAS_STATE(state, INIT)){
        draw_ptr = &ani_init;
        if(ani_init.State()==AniPlayState::PAUSING)
            ani_init.Play();
        if(ani_init.State()==AniPlayState::STOPING)
            stand();
    }
    ani_walk.Update();
    ani_init.Update();
}

void MainRole::stand(){
    draw_ptr = &tex_stand;
    SET_STATE(state, STAND);
}

void MainRole::control(){
    Director* director = Director::GetInstance();
    aim_dir = Director::GetInstance()->GetMousePos()-Position();
    const float speed = 10;
    stand();
    if(director->KeyState(SDLK_w)==KeyState::PRESSING){
        colliobj.physic_info.v.y = speed;
        walk();
    }
    if(director->KeyState(SDLK_a)==KeyState::PRESSING){
        colliobj.physic_info.v.x = -speed;
        walk();
    }
    if(director->KeyState(SDLK_s)==KeyState::PRESSING){
        colliobj.physic_info.v.y = -speed;
        walk();
    }
    if(director->KeyState(SDLK_d)==KeyState::PRESSING){
        colliobj.physic_info.v.x = speed;
        walk();
    }
    if(director->MouseButtonState(SDL_BUTTON_RIGHT)==KeyState::PRESSED){
        bomb();
    }
    if(director->MouseButtonState(SDL_BUTTON_LEFT)==KeyState::PRESSED)
        shoot();
}

void MainRole::walk(){
    draw_ptr = &ani_walk;
    SET_STATE(state, WALK);
    if(ani_walk.State()==AniPlayState::STOPING)
        ani_walk.Replay();
}

void MainRole::die_logic() {
    TextureSheet ts("resources/mainrole_die.png", 4, 1);
    ts.Scale(3, 3);
    OneUseAnimation* ani_die = OneUseAnimation::Create();
    ani_die->Load(ts, {10, 10, 10, 500});
    ani_die->MoveTo(Position().x, Position().y);
    WorldModel::GetInstance()->AddGameObject("object", ani_die);
    WorldModel::GetInstance()->TakeAway("object", GetID());
    ColliSystem::GetInstance()->DeleteElem(GetID());
    StaticTexture* gameover_tex = StaticTexture::Create();
    gameover_tex->Load("resources/GameOver.png");
    gameover_tex->Scale(10, 10);
    gameover_tex->MoveTo(Director::GetInstance()->Width()/2, Director::GetInstance()->Height()/2+100);
    WorldModel::GetInstance()->AddGameObject("object", gameover_tex);
}

void MainRole::draw() {
    draw_ptr->Draw(Position().x, Position().y);
}

MainRole::~MainRole(){
    ColliSystem::GetInstance()->DeleteElem(GetID());
}
