#include "ColliSystem.hpp"

ColliSystem* ColliSystem::instance = nullptr;

ColliSystem* ColliSystem::GetInstance(){
    if(!instance)
        instance = new ColliSystem;
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

void ColliSystem::DeleteElem(unsigned int id){
    //这里使用count记录被删除的元素。这里使用循环用来删除所有同样ID的物体（因为程序员可能不小心将同一个物体放入多次放入ColliSystem中)
    int count = 0;
    do{
        count = 0;
        for(int i=0;i<dmgSprites.size();i++)
            if(dmgSprites[i]->GetID()==id){
                dmgSprites.erase(dmgSprites.begin()+i);
                count++;
                break;
            }
    }while(count!=0);
    do{
        count = 0;
        for(int i=0;i<colliSprites.size();i++)
            if(colliSprites[i]->GetID()==id){
                colliSprites.erase(colliSprites.begin()+i);
                count++;
                break;
            }
    }while(count!=0);
}

void ColliSystem::AddColliable(ColliableSprite* cs){
    colliSprites.push_back(cs);
}

void ColliSystem::AddDamageable(DamageableSprite* ds){
    dmgSprites.push_back(ds);
}

void ColliSystem::Update(){
    for(int i=0;i<dmgSprites.size();i++){
        for(int j=i+1;j<dmgSprites.size();j++){
            Manifold m;
            if(Collision(&dmgSprites.at(i)->GetColliObject(), &dmgSprites[j]->GetColliObject(), m)){
                ColliDealFunc(m, &dmgSprites.at(i)->prop, &dmgSprites.at(j)->prop);
            }
        }
        for(int j=0;j<colliSprites.size();j++){
            Manifold m;
            if(Collision(&dmgSprites.at(i)->GetColliObject(), &colliSprites.at(j)->GetColliObject(), m)){
                ColliDealFunc(m, &dmgSprites.at(i)->prop, nullptr);
            }
        }
    }

    for(int i=0;i<colliSprites.size();i++){
        for(int j=i+1;j<colliSprites.size();j++){
            Manifold m;
            if(Collision(&colliSprites.at(i)->GetColliObject(), &colliSprites.at(j)->GetColliObject(), m)){
                ColliDealFunc(m, nullptr, nullptr);
            }
        }   
    }
}
