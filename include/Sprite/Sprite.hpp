#ifndef SPRITE_HPP
#define SPRITE_HPP
#include "Director.hpp"
#include "Colliable.hpp"
#include "HelpFunc.hpp"
#include "GameObject.hpp"
#include <list>
#include <string>
using namespace std;

class Sprite : public GameObject{
public:
    Sprite();   /** 构造函数不给出，子类应当创建自己的工厂方法 */
    virtual void Init() = 0;
    Vec TopLeft() const;
};

/**
 * @brief 可以进行碰撞检测的精灵
 */
class ColliableSprite : public Sprite, public Colliable{
public:
    void Move(float dx, float dy) override;
    void MoveTo(float x, float y) override;
    virtual Vec Position() const override;
    void update() override; 
protected:
    ColliableSprite();
};

#endif
