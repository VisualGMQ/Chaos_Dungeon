#include "Sprite/ObjJunkRecycle.hpp"

void ObjJunkRecycle(){
    if(GameObject::GameObject::_delete_all){
        while(!GameObject::_objects.empty()){
            GameObject* obj = GameObject::_objects.back();
            GameObject::_objects.pop_back();
            //TODO 在这里加上RECYCLE_FINALCLASS_BY_INSTANCE宏 
            RECYCLE_FINALCLASS_BY_INSTANCE(MainRole, GameObject::_objects, obj)
            RECYCLE_FINALCLASS_BY_INSTANCE(LittleRobo, GameObject::_objects, obj)
            RECYCLE_FINALCLASS_BY_INSTANCE(Wall, GameObject::_objects, obj)
            RECYCLE_FINALCLASS_BY_INSTANCE(Bullet, GameObject::_objects, obj)
            RECYCLE_FINALCLASS_BY_INSTANCE(OneUseAnimation, GameObject::_objects, obj)
            RECYCLE_FINALCLASS_BY_INSTANCE(StaticTexture, GameObject::_objects, obj)
            RECYCLE_FINALCLASS_BY_INSTANCE(OneUseWave, GameObject::_objects, obj)
            RECYCLE_FINALCLASS_BY_INSTANCE(Bomb, GameObject::_objects, obj)
        }
        GameObject::_objects.clear();
        GameObject::_willdel_list.clear();
        GameObject::_delete_all = false;
    }else{
        while(!GameObject::_willdel_list.empty()){
            unsigned int id = GameObject::_willdel_list.back();
            GameObject::_willdel_list.pop_back();
            for(auto i=GameObject::_objects.begin();i!=GameObject::_objects.end();i++){
                if((*i)->GetID()==id){
                    //TODO 在这里加上RECYCLE_FINALCLASS_BY_ITER的宏
                    RECYCLE_FINALCLASS_BY_ITER(MainRole, GameObject::_objects, i)
                    RECYCLE_FINALCLASS_BY_ITER(LittleRobo, GameObject::_objects, i)
                    RECYCLE_FINALCLASS_BY_ITER(Wall, GameObject::_objects, i)
                    RECYCLE_FINALCLASS_BY_ITER(Bullet, GameObject::_objects, i)
                    RECYCLE_FINALCLASS_BY_ITER(OneUseAnimation, GameObject::_objects, i)
                    RECYCLE_FINALCLASS_BY_ITER(StaticTexture, GameObject::_objects, i)
                    RECYCLE_FINALCLASS_BY_ITER(OneUseWave, GameObject::_objects, i)
                    RECYCLE_FINALCLASS_BY_ITER(Bomb, GameObject::_objects, i)
                }
            }
        }
    }
}
