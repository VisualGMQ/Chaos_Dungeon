#include "Sprite/WorldModel.hpp"

Layer::Layer(string name){
    this->name = name;
}

void Layer::AddGameObject(GameObject* obj){
    auto it = objs.begin();
    for(;it!=objs.end();it++)
        if((*it)->GetID()==obj->GetID())
            return;
    objs.push_back(obj);
}

void Layer::RemoveObject(IDType id){
    will_remove.push_back(id);
}

void Layer::TakeAway(IDType id){
    will_takeaway.push_back(id);
}

void Layer::TakeAwayAll(){
    objs.clear();
}

void Layer::JunkRecycle(){
    takeAwayRecycle();
    removeRecycle();
}

void Layer::EnableOrder(){
    isorder = true;
}

void Layer::DisableOrder(){
    isorder = false;
}

bool Layer::IsOrderDraw() const{
    return isorder;
}

void Layer::Update(){
    JunkRecycle();
    if(isorder){
        objs.sort([](const GameObject* o1, const GameObject* o2){
                return o1->Position().y>=o2->Position().y;
                });
    }
    for(GameObject* obj : objs)
        obj->Update();
}

string Layer::GetName() const{
    return name;
}

void Layer::SetName(string n) {
    name = n;
}

void Layer::Clear(){
    while(!objs.empty()) {
        objs.back()->DeleteSelf();
        objs.pop_back();
    }
}

void Layer::takeAwayRecycle(){
    while(!will_takeaway.empty()){
        IDType id = will_takeaway.back();
        will_takeaway.pop_back();
        for(auto it=objs.begin();it!=objs.end();it++)
            if((*it)->GetID()==id){
                objs.erase(it);
                break;
            }
    }
}

void Layer::removeRecycle(){
    while(!will_remove.empty()){
        IDType id = will_remove.back();
        will_remove.pop_back();
        for(auto it=objs.begin();it!=objs.end();it++)
            if((*it)->GetID()==id){
                objs.erase(it);
                (*it)->DeleteSelf();
                break;
            }
    }
}

Layer::~Layer(){
    Clear(); 
}

WorldModel* WorldModel::instance = nullptr;
list<string> WorldModel::willdel_list;
list<string> WorldModel::will_takeaway;
bool WorldModel::clear_all = false;

WorldModel* WorldModel::GetInstance(){
    if(!instance){
        instance = new WorldModel;
    }
    return instance;
}

WorldModel::WorldModel(){
    CreateLayer("main");
}

void WorldModel::Destroy(){
    delete instance;
}

void WorldModel::AddGameObject(string layer, GameObject* obj){
    GetLayer(layer)->AddGameObject(obj);
}

void WorldModel::Clear(){
    for(auto it=layers.begin();it!=layers.end();it++)
        (*it)->Clear();
}

void WorldModel::ClearWorldModel(){
    for(Layer* layer : layers)
        delete layer;
    layers.clear();
}

void WorldModel::TakeAwayAll(){
    for(Layer* layer : layers)
        layer->TakeAwayAll();
}

void WorldModel::TakeAway(string layer, IDType id){
    GetLayer(layer)->TakeAway(id);
}

void WorldModel::TakeAway(IDType id){
    for(Layer* layer : layers)
        layer->TakeAway(id);
}

void WorldModel::DeleteLayer(string name){
    willdel_list.push_back(name);
}

void WorldModel::DeleteElem(string layer, IDType id){
    GetLayer(layer)->RemoveObject(id);
}

void WorldModel::TakeAwayLayer(string name){
    will_takeaway.push_back(name);
}

void WorldModel::MoveLayer(string name, int pos){
    if(layers.empty())
        return;
    Layer* layer = GetLayer(name);
    int idx = GetLayerIdx(name);
    for(auto it=layers.begin();it!=layers.end();it++)
        if((*it)->GetName()==name){
            layers.erase(it);
            break;
        }
    if(pos>=layers.size()+1)
        layers.push_back(layer);
    else if(pos<=idx){
        auto it = layers.begin();
        std::advance(it, pos);
        layers.insert(it, layer);
    }else{
        auto it = layers.begin();
        std::advance(it, pos-1);
        layers.insert(it, layer);
    }       
}

void WorldModel::DeleteElem(IDType id){
    for(Layer* layer : layers)
        layer->RemoveObject(id);
}

Layer* WorldModel::GetLayer(string name){
    for(auto it=layers.begin();it!=layers.end();it++)
        if((*it)->GetName()==name)
            return *it;
    cerr<<"layer"<<name<<" not exists"<<endl;
    return nullptr;
}

void WorldModel::Update(){
    for(Layer* layer : layers)
        layer->Update();
}

int WorldModel::GetLayerIdx(string name) const{
    int i=0;
    for(Layer* layer : layers){
        if(name==layer->GetName())
            return i;
        i++;
    }
    return -1;
}

Layer* WorldModel::CreateLayer(string name, bool isorder){
    if(!ExistsLayer(name)){
        Layer* newlayer = new Layer(name);
        if(isorder)
            newlayer->EnableOrder();
        layers.push_back(newlayer);
        return newlayer;
    }else{
        cerr<<"warning: layer "<<name<<" already exists"<<endl;
        return nullptr;
    }
}

bool WorldModel::ExistsLayer(string name){
    for(auto it=layers.begin();it!=layers.end();it++)
        if((*it)->GetName()==name)
            return true;
    return false;
}

void WorldModel::junkRecycle(){
    while(!will_takeaway.empty()){
        string name = will_takeaway.back();
        will_takeaway.pop_back();
        for(auto it=layers.begin();it!=layers.end();it++){
            if((*it)->GetName()==name){
                layers.erase(it);
                break;
            }
        }
    }

    if(clear_all){
        while(!layers.empty()){
            delete layers.back();
            layers.pop_back();
        }
        clear_all = false;
    }else{
        while(!willdel_list.empty()){
            string name = willdel_list.back();
            willdel_list.pop_back();
            for(auto i=layers.begin();i!=layers.end();i++){
                if((*i)->GetName()==name){
                    delete *i;
                    layers.erase(i);
                    break;
                }
            }
        }
    }
}

WorldModel::~WorldModel(){
    ClearWorldModel();
}
