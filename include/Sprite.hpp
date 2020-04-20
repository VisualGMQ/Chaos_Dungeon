#ifndef SPRITE_HPP
#define SPRITE_HPP
#include "Director.hpp"
#include "Animation.hpp"
#include "Collision.hpp"

/**
 * @brief 精灵类的通用接口
 */
class ISprite{
public:
    ISprite();
    virtual void Move(float dx, float dy) = 0;
    virtual void MoveTo(float x, float y) = 0;
    void Show();
    void Hide();
    void SetSize(int w, int h);
    Size GetSize() const;
    bool IsShown() const;
    void Flip(FlipFlag flag);
    FlipFlag GetFlipFlag() const;
    void Rotate(float ddeg);
    void RotateTo(float deg);
    float GetDegree() const;
    virtual void Draw() = 0;
    virtual void Update() = 0;
protected:
    bool isshow;
    unsigned char fflag;
    float degree;
    Size size;
};

/**
 * @brief 静态精灵，即不参与碰撞检测的精灵,内部存储Texture
 */
class StaticSpriteT : public ISprite{
public:
    StaticSpriteT() = default;
    StaticSpriteT(string filename);
    void LoadTexture(string filename);
    void Move(float dx, float dy) override;
    void MoveTo(float x, float y) override;
    void Draw() override;
    void Update() override;
private:
    Texture texture;
    Vec position;
};

/**
 * @brief 静态精灵，即不参与碰撞检测的精灵,内部存储Animation
 */
class StaticSpriteAT : public ISprite{
public:
    StaticSpriteAT() = default;
    StaticSpriteAT(Animation ani);
    Animation& GetAni();
    void SetAnimationT(Animation ani);
    void Move(float dx, float dy) override;
    void MoveTo(float x, float y) override;
    void Draw() override;
    void Update() override;
protected:
    Animation animation;
private:
    Vec position;
};

/**
 * @brief 静态精灵，即不参与碰撞检测的精灵,内部存储AnimationS
 */
class StaticSpriteAS : public ISprite{
public:
    StaticSpriteAS() = default;
    StaticSpriteAS(AnimationS ani);
    AnimationS& GetAni();
    void SetAnimationS(AnimationS ani);
    void Move(float dx, float dy) override;
    void MoveTo(float x, float y) override;
    void Draw() override;
    void Update() override;
protected:
    AnimationS animation;
private:
    Vec position;
};

#endif
