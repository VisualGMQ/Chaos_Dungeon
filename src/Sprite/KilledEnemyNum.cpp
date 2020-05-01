#include "Sprite/KilledEnemyNum.hpp"

KilledEnemyNum_Sington* KilledEnemyNum_Sington::instance = nullptr;

KilledEnemyNum_Sington* KilledEnemyNum_Sington::GetInstance(){
    if(!instance)
        instance = new KilledEnemyNum_Sington;
    return instance;
}

KilledEnemyNum_Sington::KilledEnemyNum_Sington():enemy_num(0){
    num = Number::Create();
    num->SetNum(0);
    tex.Load("resources/enemy_ico.png");
}

void KilledEnemyNum_Sington::IncreaseOneNum(){
    enemy_num++;
    num->SetNum(enemy_num);
}

void KilledEnemyNum_Sington::Scale(float sx, float sy){
    num->Scale(sx, sy);
    tex.Scale(sx/2, sy/2);
}

int KilledEnemyNum_Sington::GetNum() const{
    return enemy_num;
}

void KilledEnemyNum_Sington::update(){
    num->SetNum(enemy_num);
}

void KilledEnemyNum_Sington::draw(){
    tex.Draw(Position().x, Position().y);
    num->MoveTo(Position().x+tex.Width()+10, Position().y);
    num->Update();
}
