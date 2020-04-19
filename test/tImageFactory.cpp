#include "SDL.h"
#include <iostream>
#include "ImageFactory.hpp"
#include "Draw.hpp"
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

    //test GetPureFilename()
    string filename = "./test.png";
    cout<<"GetPureFilename "<<filename<<":"<<GetPureFilename(filename)<<endl;
    filename = "~/Docuer/123/test.bmp";
    cout<<"GetPureFilename "<<filename<<":"<<GetPureFilename(filename)<<endl;
    filename = "test.bmp";
    cout<<"GetPureFilename "<<filename<<":"<<GetPureFilename(filename)<<endl;
    
    //test Num2Str()
    int num = -32;
    cout<<"Num2Str "<<num<<":"<<Num2Str(num)<<endl;
    num = 10086;
    cout<<"Num2Str "<<num<<":"<<Num2Str(num)<<endl;

    TextureSheet ts = ReadImageFromImageSheet("resources/monster1.png", 4, 1);

    while(!isquit){
        SDL_SetRenderDrawColor(render, 100, 100, 100, 255);
        SDL_RenderClear(render);
        while(SDL_PollEvent(&event)){
            if(event.type==SDL_QUIT)
                isquit = true;
        }
        int delta = 50;
        for(int i=0;i<ts.Col();i++)
            for(int j=0;j<ts.Row();j++)
                SDL_DrawTextureFromSheet(ts, i, j, i*delta, j*delta);
        SDL_RenderPresent(render);
        SDL_Delay(30);

    }
    SDL_Quit();

} 
