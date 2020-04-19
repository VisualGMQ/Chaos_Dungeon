#ifndef ANIMATION_HPP
#define ANIMATION_HPP
#include "Texture.hpp"
#include <initializer_list>
#include <vector>
#include <iostream>
using namespace std;

struct Frame{
    Frame();
    Frame(Texture tex, int delay);
    Frame(string filename, int delay);
    int delaytime; /** 按帧计*/
    Texture texture;
};

class IAnimation{
public:
    IAnimation();
    virtual void EnableLoop();
    virtual void DisableLoop();
    virtual bool IsLoop() const;
    virtual void Play();
    virtual void Stop();
    virtual void Pause();
    virtual size_t Size() const = 0;
    virtual bool Valid() const = 0;
    virtual void Update() = 0;
protected:
    int cur_frame;
    bool isplaying;
    int count;
    bool isloop;
};
/**
 * @brief 动画类，内部存储Frame
 */
class Animation : public IAnimation{
public:
    Animation() = default;
    Animation(vector<Frame> frame);
    Animation(initializer_list<Frame> frames);
    void AddFrame(string filename, int delay);
    void AddFrame(Texture texture, int delay);
    void AddFrame(Frame f);
    size_t Size() const override;
    Frame& GetCurrentFrame();
    Texture& GetCurrentTexture();
    Frame& operator[](int idx);
    bool Valid() const override;
    void Update() override;
private:
    vector<Frame> frames;
};

/**
 * @brief 动画类，内部存储TextureSheet
 * @warn 给入的TextureSheet必须是1行的
 */
class AnimationS : public IAnimation{
public:
    AnimationS() = default;
    AnimationS(TextureSheet ts, vector<int> delay);
    void SetSheet(TextureSheet ts);
    void SetDelayTimes(vector<int> delay);
    size_t Size() const override;
    SDL_Rect GetCurrentRect() const;
    bool Valid() const override;
    void Update() override;
    TextureSheet& GetSheet();
private:
    TextureSheet texsheet;
    vector<int> delaytime;
};

#endif
