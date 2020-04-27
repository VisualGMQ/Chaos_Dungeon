#include "Sprite/Sprite.hpp"

Sprite::Sprite(){
    name = "Sprite";
}

ColliableSprite::ColliableSprite(){
    name = "ColliableSprite";
}

void ColliableSprite::Move(float dx, float dy){
    colliobj.Move(dx, dy);
}

Vec ColliableSprite::Position() const {
    return colliobj.Center();
}

void ColliableSprite::MoveTo(float x, float y){
    colliobj.MoveTo(x, y);
}

void ColliableSprite::update() {
    position = colliobj.Center();
}
