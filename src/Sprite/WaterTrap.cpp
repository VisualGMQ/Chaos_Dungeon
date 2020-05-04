#include "Sprite/WaterTrap.hpp"

WaterTrap* WaterTrap::Create(){
    return new WaterTrap;
}

WaterTrap::WaterTrap():count(0){
    name = "WaterTrap";
    TextureSheet ts("./resources/trap2.png", 6, 1);
    ts.Scale(3, 3);
    ani.Load(ts, {2, 3, 3, 3, 3, 3});
    randDelayTime();
}

void WaterTrap::randDelayTime(){
    delay_shoot_time = rand()%(100-10+1)+10;
}

void WaterTrap::update(){
    if(ani.State()==AniPlayState::STOPING){
        ani.BackToFirstFrame();
        if(count==0)
            randDelayTime();
        if(count<delay_shoot_time){
            count++;
        }else{
            count = 0;
            ani.Replay();
        }
    }
    if(ani.State()==AniPlayState::PLAYING){
        if(ani.CurrentIdx()==3){
            shoot();
        }
    }
    ani.Update();
}


void WaterTrap::shoot(){
    MainRole* role = MainRole::GetRole();
    if(!role || role->prop.hp<=0)
        return;
    Vec role_pos = role->Position();
    Vec aim_dir = role_pos-Position();
    Bullet* b = Bullet::Create();
    b->GetColliObject().AttachLayer(ColliLayer::ENEMY);
    const int bullet_speed = 10;
    b->SetShootVel(Position(), Normalize(aim_dir)*bullet_speed);
    WorldModel::GetInstance()->AddGameObject("bullet", b);
}

void WaterTrap::draw(){
    ani.Draw(Position().x+24, Position().y+24);
}
