#ifndef TEXTURE_HPP
#define TEXTURE_HPP
#include "GL/glew.h"
#include "SDL_image.h"
#include "SDL.h"
#include "math.hpp"
#include "Program.hpp"
#include "Director.hpp"
#include <string>
#include <iostream>
using namespace std;

class Texture{
public:
    Texture();
    Texture(const Texture& t);
    Texture& operator=(const Texture& t);
    Texture(string filename);
    Texture(SDL_Surface* surface);
    Texture Copy();
    void Load(string filename);
    void Load(SDL_Surface* surf);
    size_t Refcount() const;
    bool Valid() const;
    int Width() const;
    int Height() const;
    void Width(int w);
    void Height(int h);
    void Scale(float sx, float sy);
    void Draw(float x, float y);
    ~Texture();
private:
    void configTexture();
    void gainSurface();
    void releaseSurface();
    GLuint texid;
    SDL_Surface* surface;
    Size size;
};

#endif