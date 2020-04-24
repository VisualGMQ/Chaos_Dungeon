#include "ColliSystem.hpp"

ColliSystem ColliSystem::instance;

ColliSystem& ColliSystem::GetInstance(){
    return instance;
}

void ColliSystem::Clear(){
    ClearColliable();
    ClearDamageable();
}

void ColliSystem::ClearColliable(){
    colliSprites.clear();
}

void ColliSystem::ClearDamageable(){
    dmgSprites.clear();
}

void ColliSystem::AddColliable(ColliableSprite* cs){
    colliSprites.push_back(cs);
}

void ColliSystem::AddDamageable(DamageableSprite* ds){
    colliSprites.push_back(ds);
}

void ColliSystem::Update(){
    for(int i=0;i<dmgSprites.size();i++){
        for(int j=i+1;j<dmgSprites.size();j++){
            if(dmgSprites.at(i)->GetColliObject().GetLayer()==dmgSprites.at(j)->GetColliObject().GetLayer())//相同层的物体不会碰撞
                continue;
            Manifold m;
            if(Collision(&dmgSprites.at(i)->GetColliObject(), &dmgSprites[j]->GetColliObject(), m)){
                ColliDealFunc(m, &dmgSprites.at(i)->prop, &dmgSprites.at(j)->prop);
            }
        }
        for(int j=0;j<colliSprites.size();j++){
            if(dmgSprites.at(i)->GetColliObject().GetLayer()==colliSprites.at(j)->GetColliObject().GetLayer())//相同层的物体不会碰撞
                continue;
            Manifold m;
            if(Collision(&dmgSprites.at(i)->GetColliObject(), &colliSprites.at(j)->GetColliObject(), m))
                ColliDealFunc(m, &dmgSprites.at(i)->prop, nullptr);
        }
    }

    for(int i=0;i<colliSprites.size();i++){
        for(int j=i+1;j<colliSprites.size();j++){
            if(colliSprites.at(i)->GetColliObject().GetLayer()==colliSprites.at(j)->GetColliObject().GetLayer())//相同层的物体不会碰撞
                continue;
            Manifold m;
            if(Collision(&colliSprites.at(i)->GetColliObject(), &colliSprites.at(j)->GetColliObject(), m))
                ColliDealFunc(m, nullptr, nullptr);
        }   
    }
}
