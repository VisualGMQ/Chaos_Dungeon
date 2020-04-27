#include "Sprite/WorldModel.hpp"

WorldModel* WorldModel::instance = nullptr;
list<unsigned int> WorldModel::willdel_list;

WorldModel* WorldModel::GetInstance(){
    if(!instance){
        instance = new WorldModel;
        instance->Init();
    }
    return instance;
}

void WorldModel::Destroy(){
    if(instance)
        delete instance;
}

void WorldModel::Init(){
    role = MainRole::Create();
    role->MoveTo(350, 350);
    role->Show();
}

void WorldModel::AddColliable(ColliableSprite* sp){
    colliSp.push_back(sp);
}

void WorldModel::AddDmgable(DamageableSprite* sp){
    dmgSp.push_back(sp);
}

void WorldModel::AddSprite(Sprite* sp){
    sprites.push_back(sp);
}

void WorldModel::ClearColliable(){
    while(!colliSp.empty()){
        ColliableSprite* sp = colliSp.back();
        sp->DeleteSelf();
        colliSp.pop_back();
    }   
}

void WorldModel::ClearDmgable(){
    while(!dmgSp.empty()){
        dmgSp.back()->DeleteSelf();
        dmgSp.pop_back();
    }
}

void WorldModel::ClearSprite(){
    while(!sprites.empty()){
        sprites.back()->DeleteSelf();
        sprites.pop_back();
    }
}

void WorldModel::Clear(){
    ClearSprite();
    ClearDmgable();
    ClearColliable();
}

void WorldModel::DeleteElem(unsigned int id){
    willdel_list.push_back(id);
}

void WorldModel::EventHandle(SDL_Event& event){
    for(auto i=colliSp.begin();i!=colliSp.end();i++)
        (*i)->EventHandle(event);
    for(auto i=sprites.begin();i!=sprites.end();i++)
        (*i)->EventHandle(event);
    for(auto i=dmgSp.begin();i!=dmgSp.end();i++)
        (*i)->EventHandle(event);
    role->EventHandle(event);
}

void WorldModel::Update(){
    Bullet::Delete();
    MainRole::Delete();
    LittleRobo::Delete();
    for(auto i=colliSp.begin();i!=colliSp.end();i++)
        (*i)->Update();
    for(auto i=sprites.begin();i!=sprites.end();i++)
        (*i)->Update();
    for(auto i=dmgSp.begin();i!=dmgSp.end();i++)
        (*i)->Update();
    role->Update();
    realDelete();
}

void WorldModel::realDelete(){
    while(!willdel_list.empty()){
        unsigned int id = willdel_list.back();
        willdel_list.pop_back();
        for(auto i=colliSp.begin();i!=colliSp.end();i++)
            if((*i)->GetID()==id){
                colliSp.erase(i);
                break;
            }
        for(auto i=sprites.begin();i!=sprites.end();i++)
            if((*i)->GetID()==id){
                sprites.erase(i);
                break;
            }
        for(auto i=dmgSp.begin();i!=dmgSp.end();i++)
            if((*i)->GetID()==id){
                dmgSp.erase(i);
                break;
            }
    }
}

WorldModel::~WorldModel(){
    ClearColliable();
    ClearSprite();
    ClearDmgable();
    role->DeleteSelf();
}
