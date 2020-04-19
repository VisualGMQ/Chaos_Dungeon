#include "SDL.h"
#include "Collision.hpp"
#include "Draw.hpp"
#include <iostream>
#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH 800
using namespace std;

int main(int argc, char** argv){
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow("title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* render = SDL_CreateRenderer(window, -1, 0);
    SDL_Event event;
    bool isquit = false;

    Object obj1(Circle(500, 500, 100)), obj2(Circle(510, 500, 50));
    Manifold m(&obj1, &obj2);
    Circle* c1 = obj1.GetCircle(); 
    Circle* c2 = obj2.GetCircle();
    while(!isquit){
        SDL_SetRenderDrawColor(render, 100, 100, 100, 255);
        SDL_RenderClear(render);
        while(SDL_PollEvent(&event)){
            if(event.type==SDL_QUIT)
                isquit = true;
            if(event.type==SDL_MOUSEMOTION){
                c1->center = Vec(event.motion.x, event.motion.y);
            }
        }
        Vec o12o2 = c1->center-c2->center;
        if(CirclevsCircle(m)){
            Vec shift = m.dir*m.deepth/2;
            if(o12o2.Dot(m.dir)>0){
                c1->center += shift;
                c2->center -= shift;
            }else{
                c1->center -= shift;
                c2->center += shift;
            }
            SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
        }else{
                SDL_SetRenderDrawColor(render, 0, 255, 0, 255);
        }
        SDL_DrawCircle(render, *c1);
        SDL_DrawCircle(render, *c2);
        SDL_RenderPresent(render);
        SDL_Delay(30);
    }
    SDL_Quit();
} 
