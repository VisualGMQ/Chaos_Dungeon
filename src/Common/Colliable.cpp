#include "Colliable.hpp"

Object& Colliable::GetColliObject(){
    if(!colliobj.Valid())
        cerr<<"warn: colliobj is invalid"<<endl;
    return colliobj;
}
