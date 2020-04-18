#ifndef GAMEBODY_HPP
#define GAMEBODY_HPP
#include "SDL.h"
#include "Director.hpp"
#include "SDL_ttf.h"
#include "SDL_image.h"
#include <iostream>
using namespace std;

class GameBody{
public:
    GameBody();
    void Update();
    ~GameBody();
protected:
    void eventHandle();
    void step();
};

#endif
