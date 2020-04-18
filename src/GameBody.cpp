#include "GameBody.hpp"

GameBody::GameBody(){
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG);
    TTF_Init();
    SDL_Window* window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    if(!window){
        cerr<<"window can't create"<<endl;
    }
    SDL_Renderer* render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    if(!render){
        cerr<<"render can't create"<<endl;
    }
    Director::Init(window, render, 30);
}

void GameBody::Update(){
    Director* direct = Director::GetInstance();
    SDL_Renderer* render = direct->GetRender();
    if(render==nullptr)
        cerr<<"render is nullptr"<<endl;
    SDL_Event& event = direct->GetEvent();
    while(!direct->IsQuit()){
        SDL_SetRenderDrawColor(render, 100, 100, 100, 255);
        SDL_RenderClear(render);
        while(SDL_PollEvent(&event)){
            if(event.type==SDL_QUIT)
                direct->Exit();
            eventHandle();
        }
        step();
        SDL_RenderPresent(render);
        SDL_Delay(1000.0/direct->fps);
    }
}

void GameBody::eventHandle(){

}

void GameBody::step(){

}

GameBody::~GameBody(){
    Director::Quit();
    SDL_DestroyWindow(Director::GetInstance()->GetWindow());
    SDL_DestroyRenderer(Director::GetInstance()->GetRender());
    SDL_Quit();
    TTF_Quit();
    IMG_Quit();
}
