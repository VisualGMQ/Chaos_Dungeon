#include "SDL.h"
#include "SDL_image.h"
#include "Texture.hpp"
#include "Draw.hpp"
#include <iostream>
using namespace std;

int main(int argc, char** argv){
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
    SDL_Window* window = nullptr;
    SDL_Renderer* render = nullptr;
    SDL_CreateWindowAndRenderer(800, 600, SDL_WINDOW_SHOWN, &window, &render);
    Director::Init(window, render, 60);
    Texture texture("resources/test.png");
    cout<<"before copy, refcount:"<<texture.GetRefcount()<<endl;
    cout<<"size:"<<texture.Width()<<","<<texture.Height()<<endl;
    {
        Texture t2 = texture;
        cout<<"after copy, refcount:"<<texture.GetRefcount()<<endl;
    }
    cout<<"after copy item released, refcount:"<<texture.GetRefcount()<<endl;
    cout<<"confirm item is exist, size:"<<texture.Width()<<","<<texture.Height()<<endl;

    TextureSheet ts("resources/monster1.png", 4, 1);
    TextureSheet ts2 = ts;

    SDL_Event event;
    bool isquit = false;
    if(!texture.Valid())
        cerr<<"Texture valid"<<endl;
    while(!isquit){
        SDL_SetRenderDrawColor(render, 100, 100, 100, 255);
        SDL_RenderClear(render);
        while(SDL_PollEvent(&event)){
            if(event.type==SDL_QUIT)
                isquit = true;
        }
        for(int i=0;i<ts.Col();i++)
            for(int j=0;j<ts.Row();j++){
                SDL_DrawTextureFromSheet(ts, i, j, i*50, j*50, 64, 64);
                SDL_DrawTextureFromSheet(ts2, i, j, i*50, j*50+100, 64, 64);
            }
        SDL_DrawTexture(texture, 100, 100, 100, 100, 60);
        SDL_RenderPresent(render);
        SDL_Delay(30);
    }
    return 0;
}
