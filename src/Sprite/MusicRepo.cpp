#include "Sprite/MusicRepo.hpp"

map<string, Mix_Music*> MusicRepo::musics;

void MusicRepo::AddMusic(string key, string filename){
    if(musics.empty() || musics.find(key)==musics.end()){
        Mix_Music* music = Mix_LoadMUS(filename.c_str());
        if(!music){
            cerr<<filename<<" music can't load."<<Mix_GetError()<<endl;
        }else{
            musics[key] = music;
        }
    }
}

Mix_Music* MusicRepo::Get(string name){
    return musics.at(name);
}

void MusicRepo::RemoveMusic(string key){
    if(musics.find(key)!=musics.end()){
        Mix_FreeMusic(musics.at(key));
        musics.erase(key);
    }
}

void MusicRepo::Quit(){
    while(!musics.empty()){
        auto it = musics.begin();
        Mix_FreeMusic(it->second);
        musics.erase(it->first);
    }
}
