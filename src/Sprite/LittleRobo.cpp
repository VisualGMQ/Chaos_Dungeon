#include "Sprite/LittleRobo.hpp"

LittleRobo* LittleRobo::Create(){
    auto* robo = new LittleRobo;
    robo->Init();
    return robo;
}

LittleRobo::LittleRobo():state(State::STAND),die_count(0),hori_flag(FlipFlag::NONE){
    name = "LittleRobo";
    prop.can_damage = false;
    tex_stand.Load("resources/monster1_stand.png");
    tex_stand.Scale(3, 3);
    TextureSheet ts_walk("resources/monster1_walk.png", 2, 1);
    ts_walk.Scale(3, 3);
    ani_walk.Load(ts_walk, {5, 5});
    ani_walk.EnableLoop();
    TextureSheet ts_att("resources/monster1_attack.png", 7, 1);
    ts_att.Scale(3, 3);
    ani_attack.Load(ts_att, {2, 2, 2, 3, 2, 2, 2});
    ani_attack.BindProp(&prop);
    ani_attack.SetColliRange(3, 4, 1);
    colliobj.Set(AABB(Position().x-tex_stand.Size().w/2, Position().y-tex_stand.Size().h/2, tex_stand.Width(), tex_stand.Height()));
    draw_ptr = &tex_stand;
    colliobj.AttachLayer(ColliLayer::ENEMY);
    ColliSystem::GetInstance()->AddDamageable(this);
}

void LittleRobo::Collied(Object* oth, BasicProp* prop, const Manifold* m){
    if(HAS_STATE(oth->GetColliType(), ColliType::BULLETABLE || HAS_STATE(oth->GetColliType(), ColliType::WAVEABLE))){
        TextureSheet ts("resources/buster2.png", 5, 1);
        ts.Scale(3, 3);
        OneUseAnimation* ani = OneUseAnimation::Create();
        ani->Load(ts, {1, 1, 1, 1, 1});
        ani->MoveTo(Position().x, Position().y);
        WorldModel::GetInstance()->AddGameObject("effect", ani);
    }
}

void LittleRobo::Init() {
    die_time_count = 0;
    prop.hp = 4;
    prop.damage = 0;
}

void LittleRobo::Stand(){
    state = State::STAND;
    draw_ptr = &tex_stand;
}

void LittleRobo::Attack(){
    state = State::ATTACK;
    draw_ptr = &ani_attack;
    if(ani_attack.State()!=AniPlayState::PLAYING){
        ani_attack.Stop();
        ani_attack.BackToFirstFrame();
        ani_attack.Play();
    }
}

void LittleRobo::Die(){
    state = State::DIE;
}

void LittleRobo::Walk(Vec vel){
    state = State::WALK;
    draw_ptr = &ani_walk;
    if(ani_walk.State()!=AniPlayState::PLAYING){
        ani_walk.Stop();
        ani_walk.Play();
    }
    colliobj.physic_info.v = vel;
}

void LittleRobo::update() {
    Creature::update();
    ani_walk.Update();
    ani_attack.Update();
}

void LittleRobo::alive_logic(){
    MainRole* role = MainRole::GetRole();
    if(!role || role->prop.hp<=0){
        Stand();
        colliobj.physic_info.v.Set(0, 0);
        return;
    }
    Vec role_pos = role->Position();
    if(role_pos.x<Position().x)
        hori_flag = FlipFlag::HORIZENTAL;
    else
        hori_flag = FlipFlag::NONE;
    //如果在规定距离，则攻击主角
    const int attackable_dist = 40;
    if(Distance(role_pos, Position())<attackable_dist){
        Attack();
        ani_walk.Stop();
        colliobj.physic_info.v.Set(0, 0);
    }else{ //当主角在的时候走向主角
        Walk(Normalize(role->Position()-Position())*5);
        ani_attack.Stop();
    }
}
void LittleRobo::die_logic(){
    TextureSheet ts("resources/monster1_die.png", 1, 1);
    ts.Scale(3, 3);
    OneUseAnimation* ani = OneUseAnimation::Create();
    ani->Flip(hori_flag);
    ani->Load(ts, {100});
    ani->MoveTo(Position().x, Position().y);
    WorldModel::GetInstance()->AddGameObject("object", ani);
    ColliSystem::GetInstance()->DeleteElem(GetID());
    WorldModel::GetInstance()->DeleteElem(GetID());
    KilledEnemyNum_Sington::GetInstance()->IncreaseOneNum();
}

void LittleRobo::draw() {
    draw_ptr->Draw(Position().x, Position().y, 0, hori_flag);
}

LittleRobo::~LittleRobo(){
    ColliSystem::GetInstance()->DeleteElem(GetID());
}
