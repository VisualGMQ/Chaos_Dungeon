#include "Sprite/Timer.hpp"

Timer* Timer::Create(){
    return new Timer;
}

Timer::Timer(){
    tex_colon.Load("resources/colon.png");
    tex_ico.Load("resources/timer_ico.png");
    Reset();
    num = Number::Create();
    tick = SDL_GetTicks();
}

void Timer::IncreaseSecond(float second){
    sec += second;
    if(sec>=60){
        sec = 0;
        min++;
    }
    if(min>=60){
        min = 0;
        hour++;
    }
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
    IncreaseSecond((SDL_GetTicks()-tick)/1000.0);
    tick = SDL_GetTicks();
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
}

Timer::~Timer(){
    num->DeleteSelf();
}
