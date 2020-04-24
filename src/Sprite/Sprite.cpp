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

void Sprite::Move(float dx, float dy){
    position.x += dx;
    position.y += dy;
}

void Sprite::MoveTo(float x, float y){
    position.Set(x, y);
}

bool Sprite::IsShow() const{
    return isshow;
}

void Sprite::Update(){
    update();
    if(IsShow())
        draw();
}

void ColliableSprite::Move(float dx, float dy){
    colliobj.Move(dx, dy);
}

void ColliableSprite::MoveTo(float x, float y){
    colliobj.MoveTo(x, y);
}

void ColliableSprite::update() {
    position = colliobj.Center();
}
