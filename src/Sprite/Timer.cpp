#include "Sprite/Timer.hpp"

Timer* Timer::Create(){
    return new Timer;
}

Timer::Timer(){
    start = false;
    tex_colon.Load("resources/colon.png");
    tex_ico.Load("resources/timer_ico.png");
    Reset();
    num = Number::Create();
    tick = SDL_GetTicks();
}

void Timer::IncreaseMilliSecond(int millisec){
    this->millisec += millisec;
    if(this->millisec>=1000){
        sec++;
        this->millisec = 0;
    }
    if(sec>=60){
        sec = 0;
        min++;
    }
    if(min>=60){
        min = 0;
        hour++;
    }
}

void Timer::Start(){
    start = true;
}

void Timer::Stop(){
    start = false;
    Reset();
}

void Timer::Pause(){
    start = false;
}

void Timer::Reset(){
    sec = 0;
    min = 0;
    hour = 0;
}

void Timer::Scale(float sx, float sy){
    num->Scale(sx, sy);
    tex_colon.Scale(sx, sy);
    tex_ico.Scale(sx/2, sy/2);
}

void Timer::update(){
    if(start){
        IncreaseMilliSecond((SDL_GetTicks()-tick));
        tick = SDL_GetTicks();
    }
}

void Timer::draw(){
    const int padding = num->SoloSize().w/3;
    const int colon_width = tex_colon.Width();
    tex_ico.Draw(Position().x, Position().y+5);
    int offset_x = tex_ico.Width()+2;

    //draw hour, if hour is zero, don't draw it
    if(hour!=0){
        num->SetNum(hour);
        num->MoveTo(Position().x, Position().y);
        num->Update();
        offset_x = padding+num->GetSize().w;
        tex_colon.Draw(Position().x+offset_x, Position().y);
        offset_x += padding;
    }

    //draw minute
    num->SetNum(min);
    num->MoveTo(Position().x+offset_x, Position().y);
    num->Update();
    offset_x += padding+num->GetSize().w;
    tex_colon.Draw(Position().x+offset_x, Position().y);
    offset_x += padding+tex_colon.Width();

    //draw second
    num->SetNum(sec);
    num->MoveTo(Position().x+offset_x, Position().y);
    num->Update();
    offset_x += padding+num->GetSize().w;
    tex_colon.Draw(Position().x+offset_x, Position().y);
    offset_x += padding+tex_colon.Width();

    //draw millisec, 这里将millisec除以10，只显示两位，看上去比较整齐
    num->SetNum(millisec/10);
    num->MoveTo(Position().x+offset_x, Position().y);
    num->Update();
}

Timer::~Timer(){
    num->DeleteSelf();
}
