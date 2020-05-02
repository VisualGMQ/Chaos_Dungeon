#include "Sprite/RangeThrower.hpp"

Boomerange* Boomerange::Create(){
    Boomerange* range = new Boomerange;
    range->Init();
    return range;
}

Boomerange::Boomerange(){
    tex.Load("resources/boomerange.png");
    colliobj.Set(OBB(Position(), tex.Width()/2, tex.Height()/2, angle));
}

void Boomerange::Init(){
    angle = 0;
    colliobj.physic_info.m = 1;
    isshooted = false;
    prop.damage = 1;
    prop.hp = 1;
}

void Boomerange::UpdateOrgPos(Vec pos){
    orgpos = pos;
}

void Boomerange::Shoot(Vec dir){
    Show();
    ColliSystem::GetInstance()->AddDamageable(this);
    shootDir = dir;
    colliobj.physic_info.f.Set(dir.x*10, dir.y*10);
    isshooted = true;
    prop.damage = 1;
    prop.hp = 1;
    prop.can_damage = true;
}

void Boomerange::update(){
    colliobj.GetOBB()->rotation.Set(angle);
    if(Distance(Position(), orgpos)<5){
        ColliSystem::GetInstance()->DeleteElem(GetID());
        Hide();
        isshooted = false;
    }
    if(!isshooted)
        angle = 0;
    else
        angle = angle>=360?angle-360:angle+5;
}

void Boomerange::draw(){
    tex.Draw(Position().x, Position().y, angle);
}

//RangeThrower

RangeThrower* RangeThrower::Create(){
    RangeThrower* rt = new RangeThrower;
    rt->Init();
    return rt;
}

RangeThrower::RangeThrower():has_boomerange(true),fflag(FlipFlag::NONE),time_count(0){
    name = "RangeThrower";
    tex_stand.Load("resources/enemy2_stand.png");
    tex_stand.Scale(3, 3);
    TextureSheet ts("resources/enemy2_walk.png", 2, 1);
    ani_walk.Load(ts, {3, 3});
    ani_walk.Scale(3, 3);
    ani_walk.EnableLoop();
    ts.Load("resources/enemy2_throw.png", 2, 1);
    ani_throw.Load(ts, {5, 3});
    ani_throw.Scale(3, 3);
    tex_boomerange.Load("resources/boomerange.png");
    tex_boomerange.Scale(3, 3);
    srand(time(nullptr));
    rand_throw_time();
    ColliSystem::GetInstance()->AddDamageable(this);
    br = Boomerange::Create();
    WorldModel::GetInstance()->AddGameObject("bullet", br);
}

void RangeThrower::rand_throw_time(){
    throw_delay_time = rand()%(1000-10+1)+10;
}

void RangeThrower::Init(){
    walk();
    colliobj.SetColliType(ColliType::DAMAGEABLE);
    colliobj.SetLayer(ColliLayer::ENEMY);
    int w = tex_stand.Width(), h = tex_stand.Height();
    colliobj.Set(AABB(Position().x-w/2, Position().y-h/2, w, h));
    prop.hp = 7;
    prop.can_damage = false;
}

void RangeThrower::stand(){
    state = State::STAND;
    draw_ptr = &tex_stand;
}

void RangeThrower::walk(){
    state = State::WALK;
    draw_ptr = &ani_walk;
    ani_walk.Play();
}

void RangeThrower::throw_range(){
    state = State::THROW;
    draw_ptr = &ani_throw;
    ani_throw.Replay();
    Vec dir = MainRole::GetRole()->Position() - Position();
    br->Shoot(dir);
}

void RangeThrower::update(){
    Creature::update();
    if(has_boomerange){
        time_count++;
        if(time_count>=throw_delay_time){
            time_count = 0;
            throw_range();
        }
    }else{
        time_count = 0;
        rand_throw_time();
    }
    ani_throw.Update();
    ani_walk.Update();
    br->UpdateOrgPos(Position());
    br->Update();
}

void RangeThrower::alive_logic(){
    if(state==State::WALK){
        approchMainrole();
    }
    if(state==State::THROW){
        if(ani_throw.State()==AniPlayState::STOPING){
            walk();
        }
    }
}

void RangeThrower::approchMainrole(){
    MainRole* role = MainRole::GetRole();
    if(!role){
        colliobj.physic_info.v.Set(0, 0);
        stand();
        return;
    }
    Vec role_pos = role->Position();
    if(role_pos.x<Position().x)
        fflag = FlipFlag::HORIZENTAL;
    else
        fflag = FlipFlag::NONE;
    const int speed = 3;
    Vec dir = Normalize(role_pos-Position());
    colliobj.physic_info.v.Set(dir.x*speed, dir.y*speed);
}

void RangeThrower::die_logic(){
    ColliSystem::GetInstance()->DeleteElem(GetID());
    WorldModel::GetInstance()->DeleteElem("object", GetID());
    OneUseAnimation* ani_die = OneUseAnimation::Create();
    TextureSheet ts("resources/enemy2_die.png", 1, 1);
    ts.Scale(3, 3);
    ani_die->Load(ts, {100});
    ani_die->MoveTo(Position().x, Position().y);
    ani_die->Flip(fflag);
    WorldModel::GetInstance()->AddGameObject("object", ani_die);
    WorldModel::GetInstance()->DeleteElem("bullet", br->GetID());
}

void RangeThrower::draw(){
    tex_boomerange.Draw(Position().x, Position().y, 0, fflag);
    draw_ptr->Draw(Position().x, Position().y, 0, fflag);
}
