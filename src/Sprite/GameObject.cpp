#include "Sprite/GameObject.hpp"

list<unsigned int> GameObject::_willdel_list;
list<GameObject*> GameObject::_objects;
IDType GameObject::cur_id = 0;
bool GameObject::_delete_all = false;

void GameObject::ClearAllObject(){
    _delete_all = true;
}

void GameObject::DeleteObject(IDType del_id){
    _willdel_list.push_back(del_id);
}

GameObject::GameObject():isshow(true),name("GameObject"),id(cur_id++){
    _objects.push_back(this);
}

void GameObject::DeleteSelf(){
    _willdel_list.push_back(GetID()) ;
}

IDType GameObject::GetID() const{
    return id;
}

void GameObject::Move(float dx, float dy){
    position.x += dx;
    position.y += dy;
}

void GameObject::MoveTo(float x, float y){
    position.Set(x, y);
}

Vec GameObject::Position() const{
    return position;
}

string GameObject::GetName() const{
    return name;
}

void GameObject::Show(){
    isshow = true;
}

bool GameObject::IsShow() const{
    return isshow;
}

void GameObject::Hide(){
    isshow = false;
}

void GameObject::Update(){
    update();
    if(IsShow()){
        draw();
    }
}
