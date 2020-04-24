#ifndef COLLIABLE_HPP
#define COLLIABLE_HPP
#include "Collision.hpp"

class Colliable{
public:
    Object& GetColliObject();
protected:
    Object colliobj;
};

#endif
