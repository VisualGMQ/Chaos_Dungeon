#ifndef TEXTURE_HPP
#define TEXTURE_HPP
#include "SDL.h"
#include "SDL_image.h"
#include "Director.hpp"
#include "math.hpp"
#include <string>
#include <iostream>
using namespace std;

enum FlipFlag : unsigned char{
    FLIP_X = 0x01,
    FLIP_Y = 0x02,
    NO_FLIP = 0x00
};

class Drawable{
public:
    /**
     * @brief 绘制图像
     * @param x 图像矩形的中点x坐标
     *          y 图像矩形的中点y坐标
     *          w 宽度，如果为0表示原始宽度
     *          h 高度，如果为0表示原始高度
     *          degree, 旋转的角度，默认不旋转
     *          flipflag 是否翻转
     * */
    virtual void Draw(int x, int y, int w = 0, int h = 0, float degree = 0, FlipFlag flipflag = NO_FLIP) = 0;
};

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

class Texture : Drawable{
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
    void Draw(int x, int y, int w = 0, int h = 0, float degree = 0, FlipFlag flipflag = NO_FLIP);
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
