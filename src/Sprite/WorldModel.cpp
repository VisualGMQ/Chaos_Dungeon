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
    if(obj->GetName()=="MainRole")
        role = (MainRole*)obj;
    //避免插入重复的物体
    auto it = objects.begin();
    for(it=objects.begin();it!=objects.end();it++)
        if((*it)->GetID()==obj->GetID())
            break;
    if(it==objects.end())
        objects.push_back(obj);
}

void WorldModel::Clear(){
    clear_all = true; 
}

MainRole* WorldModel::GetMainRole(){
    return role;
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
        IDType last_id;
        while(!objects.empty()){
            GameObject* obj = objects.back();
            obj->DeleteSelf();
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
