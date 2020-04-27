#include "Sprite/Sprite.hpp"

unsigned int Sprite::Current_ID = 0;

Sprite::Sprite():isshow(false),id(Current_ID++){}

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

unsigned int Sprite::GetID() const{
    return id;
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

list<unsigned int> StaticSprite::willdel_list;
list<StaticSprite*> StaticSprite::instances;

void StaticSprite::Init() {}

void StaticSprite::Load(string filename){
    texture.Load(filename);
}

void StaticSprite::EventHandle(SDL_Event& event) {}

void StaticSprite::update() {}

void StaticSprite::draw() {
    texture.Draw(Position().x, Position().y);
}
