#include "Sprite/Bomb.hpp"

Bomb* Bomb::Create(){
    Bomb* bomb = new Bomb;
    return bomb;
}

Bomb::Bomb():fire_time(50),time_count(0){
    name = "Bomb";
    tex.Load("resources/bomb.png");
    tex.Scale(3, 3);
    TextureSheet ts("resources/bomb_firing.png", 5, 1);
    ani_fire.Load(ts, {2, 2, 2, 2, 2});
    ani_fire.Scale(3, 3);
    ani_fire.EnableLoop();
    draw_ptr = &tex;
    colliobj.Set(Circle(Position().x, Position().y, 10));
}

void Bomb::Init(){
    state = State::SIMPLE;
}

void Bomb::Fire(){
    state = State::FIRING;
    draw_ptr = &ani_fire;
    ani_fire.Play();
}

void Bomb::update(){
    ColliableSprite::update();
    if(state==State::FIRING){
        if(time_count<fire_time)
            time_count++;
        else{
            state = State::BOMB;
            WorldModel::GetInstance()->DeleteElem(GetID());
            TextureSheet ts("resources/bomb_wave.png", 4, 1);
            ts.Scale(4, 4);
            OneUseAnimation* ani_wave = OneUseAnimation::Create();
            ani_wave->Load(ts, {2, 2, 2, 2});
            ani_wave->MoveTo(Position().x, Position().y);
            WorldModel::GetInstance()->AddGameObject("item", ani_wave);
            OneUseWave* colli_wave = OneUseWave::Create();
            colli_wave->SetWaveColliCircle(Circle(Position().x, Position().y, 60));
            colli_wave->MoveTo(Position().x, Position().y);
            colli_wave->prop.damage = 5;
            ColliSystem::GetInstance()->AddOneUseable(colli_wave);
        }
    }
    ani_fire.Update();
}

void Bomb::draw(){
    draw_ptr->Draw(Position().x, Position().y);
}
