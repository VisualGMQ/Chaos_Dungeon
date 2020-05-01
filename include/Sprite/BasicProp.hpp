/**
 * @file BasicProp.hpp
 *
 * 这个文件里面定义了人物和物体的基本属性
 *
 */
#ifndef BASICPROP_HPP 
#define BASICPROP_HPP

struct BasicProp{
    BasicProp();
    int hp;
    int damage;
    bool can_damage;
};

#endif
