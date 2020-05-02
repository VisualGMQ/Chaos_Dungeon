#include "Colliable.hpp"

Object& Colliable::GetColliObject(){
    if(!colliobj.Valid())
        cerr<<"warn: colliobj is invalid"<<endl;
    return colliobj;
}

void Colliable::Collied(Object* oth, BasicProp* prop, const Manifold* m){}

void DefaultColliFunc(Manifold* m, BasicProp* prop1, BasicProp* prop2){
    Vec v_o1o2 = m->o2->Center()-m->o1->Center();
    //如果双方都是SOLIDABLE，那么应当碰撞后分离
    if(HAS_STATE(m->o1->GetColliType(), ColliType::SOLIDABLE)&&HAS_STATE(m->o2->GetColliType(), ColliType::SOLIDABLE)){
        char sign = v_o1o2.Dot(m->dir)>=0?-1:1;
        if(m->o1->physic_info.m!=0)
            m->o1->Move(sign*m->deepth*m->dir.x, sign*m->deepth*m->dir.y);
        if(m->o2->physic_info.m!=0)
            m->o2->Move(-sign*m->deepth*m->dir.x, -sign*m->deepth*m->dir.y);
    }

    //DAMAGEABLE在碰撞之后生命值会减去对方的伤害值
    if(prop1 && prop2 && prop2->can_damage && HAS_STATE(m->o1->GetColliType(), ColliType::DAMAGEABLE)){
        prop1->hp -= prop2->damage;
        if(!HAS_STATE(m->o2->GetColliType(), ColliType::WAVEABLE))
            prop2->can_damage = false;
    }
    if(prop2 && prop2 && prop1->can_damage && HAS_STATE(m->o2->GetColliType(), ColliType::DAMAGEABLE)){
        prop2->hp -= prop1->damage;
        if(!HAS_STATE(m->o1->GetColliType(), ColliType::WAVEABLE))
            prop1->can_damage = false;
    }

    //BULLETABLE在碰撞之后会将自己的生命值减1
    if(prop1 && HAS_STATE(m->o1->GetColliType(), ColliType::BULLETABLE)){
        prop1->hp--;
    }
    if(prop2 && HAS_STATE(m->o2->GetColliType(), ColliType::BULLETABLE)){
        prop2->hp--;
    }
}
