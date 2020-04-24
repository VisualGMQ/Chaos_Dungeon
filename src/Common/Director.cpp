#include "Director.hpp"

Director* Director::director = nullptr;

void Director::Init(SDL_Window* window, int w, int h, int fps){
    if(director)
        delete director;
    director = new Director(window, w, h, fps);
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

SDL_Event& Director::GetEvent(){
    return event;
}

void Director::EventHandle(){
    if(event.type==SDL_KEYDOWN){
        keys[event.key.keysym.sym] = true;
    }
    if(event.type==SDL_KEYUP)
        keys[event.key.keysym.sym] = false;
}

KeyState Director::KeyState(SDL_Keycode keycode){
    //if key not press
    if(keys.find(keycode)==keys.end() || !keys[keycode]){
        if(oldkeys.find(keycode)==keys.end() || !oldkeys[keycode])
            return RELEASING;
        else
            return RELEASED;
    }else{  //if key pressed
        if(oldkeys.find(keycode)==keys.end() || !oldkeys[keycode])
            return PRESSED;
        else
            return PRESSING;
    }
}

int Director::Width() const{
    return width;
}

int Director::Height() const{
    return height;
}

void Director::SizeAdapt(int neww, int newh){
    glViewport(0, 0, neww, newh);
}

void Director::Update(){
    oldkeys = keys;
    glm::mat4 ortho = glm::ortho<float>(0, Width(), 0, Height());
    Program::GetInstance().UniformMat4("Ortho", ortho);
}

bool Director::IsQuit() const{
    return isquit;
}

Director::Director(SDL_Window* window, int w, int h, int fps):isquit(false),width(w),height(h){
    this->window = window;
    this->fps = fps;
}

void Director::Exit(){
    isquit = true;
}
