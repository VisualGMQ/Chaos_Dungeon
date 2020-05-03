#ifndef TIMER_HPP
#define TIMER_HPP
#include "Number.hpp"
#include "GameObject.hpp"
#include "Texture.hpp"

class Timer : public GameObject{
public:
    static Timer* Create();
    void IncreaseMilliSecond(int millisec);
    void Reset();
    void Scale(float sx, float sy);
    void Start();
    void Stop();
    void Pause();
private:
    void update() override;
    void draw() override;
    Timer();
    ~Timer();
    int hour;
    int min;
    int sec;
    int millisec;
    bool start;
    Number* num;
    Texture tex_colon;
    Texture tex_ico;
    Uint32 tick;
};

#endif
