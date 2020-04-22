#ifndef DIRECTOR_HPP
#define DIRECTOR_HPP
#include "GL/glew.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "Program.hpp"
#include "math.hpp"

class Director{
public:
    static void Init(SDL_Window* window, int w, int h, int fps);
    static void Quit();
    static Director* GetInstance();
    SDL_Window* GetWindow();
    SDL_Event& GetEvent();
    int Width() const;
    int Height() const;
    void SizeAdapt(int neww, int newh);
    void Exit();
    void Update();
    bool IsQuit() const;
    int fps;
private:
    static Director* director;
    SDL_Window* window;
    SDL_Event event;
    int width;
    int height;
    
    bool isquit;
    Director(SDL_Window* window, int w, int h, int fps);
};

#endif
