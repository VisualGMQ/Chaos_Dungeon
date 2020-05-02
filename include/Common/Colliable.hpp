#ifndef COLLIABLE_HPP
#define COLLIABLE_HPP
#include "Collision.hpp"

class Colliable{
public:
    Object& GetColliObject();
    /**
     * @brief 在判断一定碰撞后，用于执行碰撞的函数
     */
    virtual void Collied(Object* oth, BasicProp* prop, const Manifold* m);
protected:
    Object colliobj;
};

/**
 * @brief 处理碰撞检测的系统默认函数
 * @param m 碰撞检测返回的信息
 * @param obj 碰撞到的物体
 * @param prop 碰撞到的物体的基本属性
 *
 * 这个函数根据Object的碰撞分类(colli_type)来进行不同的碰撞之后的操作。
 */
void DefaultColliFunc(Manifold* m, BasicProp* prop1, BasicProp* prop2);

#endif
