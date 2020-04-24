#ifndef SPRITE_HPP
#define SPRITE_HPP
#include "Texture.hpp"
#include "TextureSheet.hpp"
#include "Animation.hpp"
#include "Director.hpp"
#include "Colliable.hpp"
#include "HelpFunc.hpp"

class Sprite{
public:
    Sprite();
    virtual void Init() = 0;
    void Show(); /** @warn 显示精灵，必须在Update里面实现对isshow变量的反馈*/
    void Hide(); /** @warn 隐藏精灵，必须在Update里面实现对isshow变量的反馈*/
    bool IsShow() const;
    Vec Position() const;
    void Move(float dx, float dy);
    void MoveTo(float x, float y);
    Vec TopLeft() const;
    /**
     * @brief 事件处理，在这里实现你人物的事件处理
     */
    virtual void EventHandle(SDL_Event& event) = 0;
    /**
     * @brief 精灵更新，每一帧需要调用一次
     */
    void Update();
protected:
    //在这里实现你的逻辑
    virtual void update() = 0;
    //在这里实现你的绘制
    virtual void draw() = 0;
    Vec position;
    bool isshow;
};

/**
 * @brief 可以进行碰撞检测的精灵
 */
class ColliableSprite : public Sprite, public Colliable{
public:
    void Move(float dx, float dy);
    void MoveTo(float x, float y);
    void update() override; 
private:
};

#endif
