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
    tex_die.Load("resources/monster1_die.png");
    tex_die.Scale(3, 3);
    tex_stand.Scale(3, 3);
    TextureSheet ts_walk("resources/monster1_walk.png", 2, 1);
    ts_walk.Scale(3, 3);
    ani_walk.Load(ts_walk, {5, 5});
    ani_walk.EnableLoop();
    TextureSheet ts_att("resources/monster1_attack.png", 7, 1);
    ts_att.Scale(3, 3);
    ani_attack.Load(ts_att, {2, 2, 2, 3, 2, 2, 2});
    colliobj.Set(AABB(Position().x-tex_stand.Size().w/2, Position().y-tex_stand.Size().h/2, tex_stand.Width(), tex_stand.Height()));
    draw_ptr = &tex_stand;
    colliobj.AttachLayer(ColliLayer::ENEMY);
    ColliSystem::GetInstance()->AddDamageable(this);
}

void LittleRobo::Init() {
    prop.hp = 2;
    prop.damage = 1;
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
        ani_attack.Play();
    }
}

void LittleRobo::Die(){
    state = State::DIE;
    draw_ptr = &tex_die;
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
    DamageableSprite::update();
    ani_walk.Update();
    ani_attack.Update();
    colliobj.Update(1.0/Director::GetInstance()->fps);

    MainRole* role = WorldModel::GetInstance()->GetMainRole();
    Vec role_pos = role->Position();
    if(role_pos.x<Position().x)
        hori_flag = FlipFlag::HORIZENTAL;
    else
        hori_flag = FlipFlag::NONE;
    //当主角在的时候走向主角
    const int attackable_dist = 40;
    if(Distance(role_pos, Position())<attackable_dist){
        Attack();
        colliobj.physic_info.v.Set(0, 0);
    }else //如果在规定距离，则攻击主角
        Walk(Normalize(role->Position()-Position())*5);
    if(state==State::ATTACK){
        int cur_frame_idx = ani_attack.CurrentIdx();
        if(cur_frame_idx>=2 && cur_frame_idx<=5){
            prop.can_damage = true;
            prop.damage = 1;
        }
        
    }

    if(prop.hp<=0)
        WorldModel::GetInstance()->DeleteElem(GetID());
}

void LittleRobo::draw() {
    draw_ptr->Draw(Position().x, Position().y, 0, hori_flag);
}

LittleRobo::~LittleRobo(){
    ColliSystem::GetInstance()->DeleteElem(GetID());
}
