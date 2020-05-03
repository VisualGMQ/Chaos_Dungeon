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

void ColliSystem::AddOneUseable(OneUseWave* ow){
    oneuseSprites.push_back(ow);
}

void ColliSystem::AddColliable(ColliableSprite* cs){
    auto it = colliSprites.begin();
    for(;it!=colliSprites.end();it++)
        if((*it)->GetID()==cs->GetID())
                break;
    if(it==colliSprites.end())
        colliSprites.push_back(cs);
}

void ColliSystem::AddDamageable(DamageableSprite* ds){
    auto it = dmgSprites.begin();
    for(;it!=dmgSprites.end();it++)
        if((*it)->GetID()==ds->GetID())
            break;
    if(it==dmgSprites.end())
        dmgSprites.push_back(ds);
}

void callColliDealFunc(Manifold* m, Colliable* obj1, Colliable* obj2, BasicProp* prop){
    obj1->Collied(&obj2->GetColliObject(), prop, m);
}

void ColliSystem::Update(){
    for(int i=0;i<dmgSprites.size();i++){
        for(int j=i+1;j<dmgSprites.size();j++){
            Manifold m;
            if(Collision(&dmgSprites.at(i)->GetColliObject(), &dmgSprites[j]->GetColliObject(), m)){
                DefaultColliFunc(&m, &dmgSprites.at(i)->prop, &dmgSprites.at(j)->prop);
                callColliDealFunc(&m, dmgSprites.at(i), dmgSprites.at(j), &dmgSprites.at(j)->prop);
                callColliDealFunc(&m, dmgSprites.at(j), dmgSprites.at(i), &dmgSprites.at(i)->prop);
            }
        }
        for(int j=0;j<colliSprites.size();j++){
            Manifold m;
            if(Collision(&dmgSprites.at(i)->GetColliObject(), &colliSprites.at(j)->GetColliObject(), m)){
                DefaultColliFunc(&m, &dmgSprites.at(i)->prop, nullptr);
                callColliDealFunc(&m, dmgSprites.at(i), colliSprites.at(j), nullptr);
                callColliDealFunc(&m, colliSprites.at(j), dmgSprites.at(i), &dmgSprites.at(i)->prop);
            }
        }
    }

    for(int i=0;i<colliSprites.size();i++){
        for(int j=i+1;j<colliSprites.size();j++){
            Manifold m;
            if(Collision(&colliSprites.at(i)->GetColliObject(), &colliSprites.at(j)->GetColliObject(), m)){
                DefaultColliFunc(&m, nullptr, nullptr);
                callColliDealFunc(&m, colliSprites.at(i), colliSprites.at(j), nullptr);
                callColliDealFunc(&m, colliSprites.at(j), colliSprites.at(i), nullptr);
            }
        }   
    }

    for(int i=0;i<oneuseSprites.size();i++){
        for(int j=0;j<dmgSprites.size();j++){
            Manifold m;
            if(Collision(&oneuseSprites.at(i)->GetColliObject(), &dmgSprites.at(j)->GetColliObject(), m)){
                DefaultColliFunc(&m, &oneuseSprites.at(i)->prop, &dmgSprites.at(j)->prop);
                callColliDealFunc(&m, oneuseSprites.at(i), dmgSprites.at(j), &dmgSprites.at(j)->prop);
                callColliDealFunc(&m, dmgSprites.at(j), oneuseSprites.at(i), &oneuseSprites.at(i)->prop);
            }   
        }
    }

    for(int i=0;i<oneuseSprites.size();i++)
        oneuseSprites[i]->DeleteSelf();
    oneuseSprites.clear();
}
