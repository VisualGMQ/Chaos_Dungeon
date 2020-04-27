#ifndef GAMEBODY_HPP
#define GAMEBODY_HPP
#define GLEW_STATIC
#include "GL/glew.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#include "Director.hpp"
#include "Program.hpp"
#include "Sprite/MainRole.hpp"
#include "Sprite/Wall.hpp"
#include "Sprite/LittleRobo.hpp"
#include "Sprite/WorldModel.hpp"
#include "ColliSystem.hpp"
#include "math.hpp"
#include "Camera.hpp"
#include "Sprite/ObjJunkRecycle.hpp"
#include <vector>
#include <iostream>
#include <map>
using namespace std;

class GameBody{
public:
    GameBody();
    void Update();
    ~GameBody();
protected:
    void init();
    void step();
    map<SDL_Keysym, bool> keys;
    Vec mouse_pos;
};

#endif
