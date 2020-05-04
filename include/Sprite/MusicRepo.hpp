#ifndef MUSICREPO_HPP
#define MUSICREPO_HPP
#include "SDL_mixer.h"
#include <map>
#include <string>
#include <iostream>
using namespace std;

class MusicRepo{
public:
    static void AddMusic(string key, string filename);
    static Mix_Music* Get(string name);
    static void RemoveMusic(string key);
    static void Quit(); 
private:
    static map<string, Mix_Music*> musics;
};

#endif
