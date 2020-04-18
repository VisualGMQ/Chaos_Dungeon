#ifndef DIRECTOR_HPP
#define DIRECTOR_HPP
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

class Director{
public:
    static void Init(SDL_Window* window, SDL_Renderer* render, int fps);
    static void Quit();
    static Director* GetInstance();
    SDL_Window* GetWindow();
    SDL_Renderer* GetRender();
    SDL_Event& GetEvent();
    void Exit();
    bool IsQuit() const;
    int fps;
private:
    static Director* director;
    SDL_Window* window;
    SDL_Renderer* render;
    SDL_Event event;
    
    bool isquit;
    Director(SDL_Window* window, SDL_Renderer* render, int fps);
};

#endif
