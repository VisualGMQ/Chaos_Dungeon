#include "Director.hpp"

Director* Director::director = nullptr;

void Director::Init(SDL_Window* window, int w, int h, int fps){
    if(director)
        delete director;
    director = new Director(window, w, h, fps);
    director->mousepos.x = 0;
    director->mousepos.y = 0;
    director->mousekeys[SDL_BUTTON_LEFT] = false;
    director->mousekeys[SDL_BUTTON_RIGHT] = false;
    director->mousekeys[SDL_BUTTON_MIDDLE] = false;
    director->mousekeys[SDL_BUTTON_X1] = false;
    director->mousekeys[SDL_BUTTON_X2] = false;
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

Vec Director::GetMousePos() const{
    return mousepos;
}

int Director::WindowWidth(){
    int w;
    SDL_GetWindowSize(window, &w, nullptr);
    return w;
}

int Director::WindowHeight(){
    int h;
    SDL_GetWindowSize(window, nullptr, &h);
    return h;
}

void Director::EventHandle(){
    if(event.type==SDL_KEYDOWN){
        keys[event.key.keysym.sym] = true;
    }
    if(event.type==SDL_KEYUP)
        keys[event.key.keysym.sym] = false;
    if(event.type==SDL_MOUSEMOTION){
        mousepos.Set(event.motion.x/static_cast<float>(WindowWidth())*Width(), (Director::GetInstance()->WindowHeight()-event.motion.y)/static_cast<float>(WindowHeight())*Height());
    }
    if(event.type==SDL_MOUSEBUTTONDOWN)
        mousekeys[event.button.button] = true;
    if(event.type==SDL_MOUSEBUTTONUP)
        mousekeys[event.button.button] = false;
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

KeyState Director::MouseButtonState(Uint8 button){
    if(oldmousekeys[button]){
        if(mousekeys[button])
            return PRESSING;
        else
            return RELEASED;
    }else{
        if(mousekeys[button])
            return PRESSED;
        else
            return RELEASING;
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
    SDL_SetWindowSize(window, neww, newh);  //这个地方必须要手动设置窗体大小。如果不设置虽然外观上大小变了，但是内部的w和h值仍然没变
}

void Director::Update(){
    oldkeys = keys;
    oldmousekeys = mousekeys;
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
