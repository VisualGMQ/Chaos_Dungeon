#include "SDL.h"
#include "Animation.hpp"
#include "ImageFactory.hpp"
#include "Draw.hpp"
#include <iostream>
#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH 800
using namespace std;

int main(int argc, char** argv){
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow("title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* render = SDL_CreateRenderer(window, -1, 0);
    Director::Init(window, render, 60);
    SDL_Event event;
    bool isquit = false;

    Animation ani({Frame("resources/test.png", 3),
                   Frame("resources/test2.bmp", 2),
                   Frame("resources/test3.bmp", 5)});
    ani.Play();
    ani.DisableLoop();
    AnimationS anis(ReadImageFromImageSheet("resources/monster1.png", 4, 1), {3, 3, 3, 3});
    anis.Play();
    anis.EnableLoop();
    SDL_Rect rect = {100, 100, 80, 80};
    while(!isquit){
        SDL_SetRenderDrawColor(render, 100, 100, 100, 255);
        SDL_RenderClear(render);
        while(SDL_PollEvent(&event)){
            if(event.type==SDL_QUIT)
                isquit = true;
        }
        ani.Update();
        anis.Update();
        SDL_DrawAnimation(ani, 100, 100);
        SDL_DrawAnimationS(anis, 100, 300, 64, 64);
        SDL_RenderPresent(render);
        SDL_Delay(100);
    }
    SDL_Quit();
} 
