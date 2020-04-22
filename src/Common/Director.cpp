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
    //glm::mat4 ortho = glm::ortho<float>(0, Director::GetInstance()->Width(), Director::GetInstance()->Height(), 0, -1.0f, 1.0f);
    //glm::mat4 model = glm::mat4(1);
    //model = glm::translate(model, glm::vec3(-0.5, -0.5, 0));
    //Program::GetInstance().UniformMat4("ortho", ortho);
    //Program::GetInstance().UniformMat4("model", model);
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
