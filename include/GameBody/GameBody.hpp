#ifndef GAMEBODY_HPP
#define GAMEBODY_HPP
#define GLEW_STATIC
#include "GL/glew.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "Director.hpp"
#include "Program.hpp"
#include "Sprite/Sprites.hpp"
#include "Sprite/WorldModel.hpp"
#include "Sprite/MusicRepo.hpp"
#include "ColliSystem.hpp"
#include "math.hpp"
#include "Camera.hpp"
#include "Sprite/ObjJunkRecycle.hpp"
#include <iostream>
#include <map>
#include <vector>
#include <ctime>
#include <random>
using namespace std;

struct TrapInfo{
    Vec pos;
    IDType id;
};

class GameBody{
public:
    GameBody();
    void Update();
    ~GameBody();
protected:
    void initCursor();
    void init();
    void randTraps();
    void game_step();
    map<SDL_Keysym, bool> keys;
    vector<TrapInfo> traps;
    Vec mouse_pos;
    SDL_Cursor* cursor;
    Timer* timer;
    SDL_Surface* surf_ico;
};

#endif
