#include "Director.hpp"

Director* Director::director = nullptr;

void Director::Init(SDL_Window* window, SDL_Renderer* render, int fps){
    if(director)
        delete director;
    director = new Director(window, render, fps);
}

void Director::Quit(){
    delete director;
}

Director* Director::GetInstance(){
    return director;
}

SDL_Window* Director::GetWindow(){
    return window;
}

SDL_Renderer* Director::GetRender(){
    return render;
}

SDL_Event& Director::GetEvent(){
    return event;
}

bool Director::IsQuit() const{
    return isquit;
}

Director::Director(SDL_Window* window, SDL_Renderer* render, int fps):isquit(false){
    this->window = window;
    this->render = render;
    this->fps = fps;
}

void Director::Exit(){
    isquit = true;
}
