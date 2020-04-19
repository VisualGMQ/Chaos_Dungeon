#ifndef TEXTURE_HPP
#define TEXTURE_HPP
#include "SDL.h"
#include "SDL_image.h"
#include "Director.hpp"
#include <string>
#include <iostream>
using namespace std;

struct _texture{
    _texture();
    _texture(SDL_Texture* tex);
    _texture(string filename);
    SDL_Texture* texture;
    void Gain();
    void Release();
    int GetRefcount() const;
private:
    int refcount;
};

class Texture{
public:
    static Texture NullTexture;
    Texture();
    Texture(string filename);
    Texture(const Texture& t);
    void Load(string filename);
    SDL_Texture* GetTexture();
    int GetRefcount() const;
    bool Valid() const;
    int Width();
    int Height();
    Texture& operator=(const Texture t);
    ~Texture();
private:
    _texture* texture;
};

class TextureSheet{
public:
    static TextureSheet NullSheet;
    TextureSheet();
    TextureSheet(string filename, int c, int r);
    void Load(string filename, int c, int r);
    bool Valid() const;
    int TotleWidth();
    int TotleHeight();
    int Width();
    int Height();
    int Col() const;
    int Row() const;
    /**
     * @brief 得到第c列第r行的图像所在的范围
     */
    SDL_Rect Get(int c, int r) const;
    Texture& GetTexture();
private:
    int col;
    int row;
    int per_w;
    int per_h;
    Texture texture;
};

#endif
