#include "Sprite/Sprite.hpp"

Sprite::Sprite():isshow(false){}

void Sprite::Show(){
    isshow = true;
}

void Sprite::Hide(){
    isshow = false;
}

Vec Sprite::Position() const{
    return position;
}

bool Sprite::IsShow() const{
    return isshow;
}

void Sprite::Update(){
    update();
    if(IsShow())
        draw();
}
