#include "Sprite.hpp"
#include "SDL.h"
#include <iostream>
#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH 800
using namespace std;

int main(int argc, char** argv){
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow("title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* render = SDL_CreateRenderer(window, -1, 0);
    Director::Init(window, render, 30);
    SDL_Event event;
    bool isquit = false;

    StaticSpriteT spt("resources/grass.png");
    StaticSpriteAS aniat(AnimationS(TextureSheet("resources/monster1.png", 4, 1), {3, 3, 3, 3}));
    aniat.SetSize(100, 100);
    aniat.GetAni().Play();
    aniat.GetAni().EnableLoop();
    cout<<"created aniat"<<endl;

    Vec pos(50, 50);
    while(!isquit){
        SDL_SetRenderDrawColor(render, 100, 100, 100, 255);
        SDL_RenderClear(render);
        while(SDL_PollEvent(&event)){
            if(event.type==SDL_QUIT)
                isquit = true;
            if(event.type==SDL_KEYDOWN) 
                pos.x += 10;
        }
        spt.MoveTo(pos.x, pos.y);
        spt.Update();
        spt.Draw();
        aniat.MoveTo(pos.x, pos.y+100);
        aniat.Update();
        aniat.Draw();
        SDL_RenderPresent(render);
        SDL_Delay(30);
    }
    SDL_Quit();
} 

