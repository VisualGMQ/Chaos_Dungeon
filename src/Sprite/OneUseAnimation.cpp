#include "Sprite/OneUseAnimation.hpp"

OneUseAnimation* OneUseAnimation::Create(){
    return new OneUseAnimation;
}

OneUseAnimation::OneUseAnimation():flipflag(FlipFlag::NONE){
    name = "OneUseAnimation";
}

void OneUseAnimation::Load(TextureSheet& ts, vector<int> delay){
    ani.Load(ts, delay);
    ani.Play();
}

void OneUseAnimation::update() {
    ani.Update();
    if(ani.State()==AniPlayState::STOPING){
        WorldModel::GetInstance()->DeleteElem(GetID());
    }
}

void OneUseAnimation::Flip(FlipFlag fflag){
    flipflag = fflag;
}

void OneUseAnimation::draw() {
    ani.Draw(Position().x, Position().y, 0, flipflag);
}
