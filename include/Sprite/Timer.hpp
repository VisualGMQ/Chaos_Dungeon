#ifndef TIMER_HPP
#define TIMER_HPP
#include "Number.hpp"
#include "GameObject.hpp"
#include "Texture.hpp"

class Timer : public GameObject{
public:
    static Timer* Create();
    void IncreaseSecond(float second);
    void Reset();
    void Scale(float sx, float sy);
private:
    void update() override;
    void draw() override;
    Timer();
    ~Timer();
    int hour;
    int min;
    float sec;
    Number* num;
    Texture tex_colon;
    Texture tex_ico;
    Uint32 tick;
};

#endif
