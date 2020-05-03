#include "Sprite/Magema.hpp"

Magema* Magema::Create(){
    Magema* m = new Magema;
    m->Init();
    return m;
}

Magema::Magema(){
    name = "Magema";
    TextureSheet ts("resources/magma.png", 6, 1);
    ts.Scale(3, 3);
    ani.Load(ts, {2, 2, 2, 2, 2, 2});
    ani.EnableLoop();
    ani.Play();
    colliobj.Set(AABB(Position().x-ts.SoloWidth()/2, Position().y-ts.SoloHeight()/2, ts.SoloWidth(), ts.SoloHeight()));
    colliobj.SetColliType(ColliType::TRAPABLE);
    colliobj.SetLayer(ColliLayer::ENEMY);
    colliobj.AttachLayer(ColliLayer::BLOCK);
    colliobj.AttachLayer(ColliLayer::BULLET);
    ColliSystem::GetInstance()->AddColliable(this);
}

void Magema::Init(){}

void Magema::update(){
    ColliableSprite::update();
    ani.Update();
}

void Magema::Collied(Object* oth, BasicProp* prop, const Manifold* m){
    if(!prop)
        return;
    if(PointInAABB(oth->Center(), *colliobj.GetAABB())){
        prop->hp = 0;
    }
}

void Magema::draw(){
    ani.Draw(Position().x, Position().y);
}

Magema::~Magema(){
    ColliSystem::GetInstance()->DeleteElem(GetID());
    WorldModel::GetInstance()->DeleteElem("item", GetID());
}

