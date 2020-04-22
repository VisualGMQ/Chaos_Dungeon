#ifndef TEXTURE_SHEET
#define TEXTURE_SHEET
#include "Texture.hpp"
#include <vector>
using namespace std;

class TextureSheet{
public:
    TextureSheet();
    TextureSheet(string filename, int col, int row);
    void Load(string filename, int col, int row);
    Texture& Get(int col, int row);
    void Scale(float sx, float sy);
    void Draw(float x, float y, int c, int r);
    void Col() const;
    void Row() const;
    bool Valid() const;
    size_t Size() const;
    vector<Texture> Images() const;
    int SoloWidth() const;
    int SoloHeight() const;
    int Width() const;
    int Height() const;
private:
    int per_w;
    int per_h;
    int col;
    int row;
    vector<Texture> textures;
};

#endif
