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

    Object obj1(OBB(Vec(300, 300), 50, 25, 30)), obj2(OBB(Vec(400, 300), 50, 25, 60));
    OBB* obb1 = obj1.GetOBB(), *obb2 = obj2.GetOBB();
    Manifold m(&obj1, &obj2);
    
    while(!isquit){
        SDL_SetRenderDrawColor(render, 100, 100, 100, 255);
        SDL_RenderClear(render);
        while(SDL_PollEvent(&event)){
            if(event.type==SDL_QUIT)
                isquit = true;
            if(event.type==SDL_MOUSEMOTION){
                obb1->center.x = event.motion.x;
                obb1->center.y = event.motion.y;
            }
        }
        Vec o12o2 = obb1->center-obb2->center;
        if(OBBvsOBB(m)){
            if(o12o2.Dot(m.dir)>0){
                obb1->center += m.dir*m.deepth;
                obb2->center -= m.dir*m.deepth;
            }else{
                obb1->center -= m.dir*m.deepth;
                obb2->center += m.dir*m.deepth;
            }
            SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
        }else{
                SDL_SetRenderDrawColor(render, 0, 255, 0, 255);
        }
        SDL_DrawOBB(render, *obb1);
        SDL_DrawOBB(render, *obb2);
        SDL_RenderPresent(render);
        SDL_Delay(30);
    }
    SDL_Quit();
} 
