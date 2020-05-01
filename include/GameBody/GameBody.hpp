#ifndef GAMEBODY_HPP
#define GAMEBODY_HPP
#define GLEW_STATIC
#include "GL/glew.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#include "Director.hpp"
#include "Program.hpp"
#include "Sprite/Sprites.hpp"
#include "Sprite/WorldModel.hpp"
#include "ColliSystem.hpp"
#include "math.hpp"
#include "Camera.hpp"
#include "Sprite/ObjJunkRecycle.hpp"
#include <vector>
#include <iostream>
#include <map>
#include <ctime>
#include <random>
using namespace std;

class GameBody{
public:
    GameBody();
    void Update();
    ~GameBody();
protected:
    void initCursor();
    void init();
    void step();
    map<SDL_Keysym, bool> keys;
    Vec mouse_pos;
    SDL_Cursor* cursor;
};

#endif
