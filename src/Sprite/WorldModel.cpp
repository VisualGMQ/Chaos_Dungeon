#include "Sprite/WorldModel.hpp"

WorldModel* WorldModel::instance = nullptr;
list<unsigned int> WorldModel::willdel_list;
bool WorldModel::clear_all = false;

WorldModel* WorldModel::GetInstance(){
    if(!instance){
        instance = new WorldModel;
    }
    return instance;
}

void WorldModel::Destroy(){
    delete instance;
}

void WorldModel::AddGameObject(GameObject* obj){
    objects.push_back(obj);
}

void WorldModel::Clear(){
    clear_all = true; 
}

void WorldModel::DeleteElem(unsigned int id){
    willdel_list.push_back(id);
}

void WorldModel::Update(){
    junkRecycle();
    for(auto & object : objects)
        object->Update();
}

void WorldModel::junkRecycle(){
    if(clear_all){
        while(!objects.empty()){
            objects.back()->DeleteSelf();
            objects.pop_back();
        }
        clear_all = false;
    }else{
        while(!willdel_list.empty()){
            IDType id = willdel_list.back();
            willdel_list.pop_back();
            for(auto i=objects.begin();i!=objects.end();i++){
                if((*i)->GetID()==id){
                    (*i)->DeleteSelf();
                    objects.erase(i);
                    break;
                }
            }
        }
    }
}

WorldModel::~WorldModel(){
    Clear();
}
