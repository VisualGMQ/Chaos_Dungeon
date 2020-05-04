#include "Sprite/Wall.hpp"

Wall* Wall::Create(){
    auto* w = new Wall;
    w->Init();
    return w;
}

Wall::Wall(){
    name = "Wall";
}

void Wall::Init() {
    texture.Load("./resources/wall.png");
    texture.Scale(3, 3);
    colliobj.Set(AABB(topleft().x, topleft().y, texture.Size().w, texture.Size().h));
    colliobj.physic_info.m = 0;
    colliobj.AttachColliType(ColliType::SOLIDABLE);
    colliobj.AttachLayer(ColliLayer::BLOCK);
    ColliSystem::GetInstance()->AddColliable(this);
}

int Wall::Width() const{
    return texture.Width();
}

Vec Wall::topleft() const{
    return Vec(Position().x-texture.Width()/2, Position().y-texture.Height()/2);
}

int Wall::Height() const{
    return texture.Height();
}

void Wall::update() {
    ColliableSprite::update();
}

void Wall::draw() {
    texture.Draw(Position().x, Position().y);
}

Wall::~Wall(){
    ColliSystem::GetInstance()->DeleteElem(GetID());
}
