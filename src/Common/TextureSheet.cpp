#include "TextureSheet.hpp"

TextureSheet::TextureSheet():col(0),row(0){}

TextureSheet::TextureSheet(string filename, int col, int row){
    Load(filename, col, row);
}

TextureSheet::TextureSheet(const TextureSheet& ts){
    *this = ts; 
}

TextureSheet& TextureSheet::operator=(const TextureSheet& ts){
    per_w = ts.per_w;
    per_h = ts.per_h;
    col = ts.col;
    row = ts.row;
    textures.assign(ts.textures.begin(), ts.textures.end());
    return *this;
}

void TextureSheet::Load(string filename, int col, int row){
    SDL_Surface* image = IMG_Load(filename.c_str());
    if(!image){
        cerr<<filename<<" can't load in TextureSheet"<<endl;
    }else{
        per_w = image->w/col;
        per_h = image->h/row;
        for(int i=0;i<col;i++)
            for(int j=0;j<row;j++){
                 SDL_Surface* surf = SDL_CreateRGBSurfaceWithFormat(0, per_w, per_h, 32, SDL_PIXELFORMAT_RGBA32);
                 SDL_Rect rect = {i*per_w, j*per_h, per_w, per_h};
                 SDL_BlitSurface(image, &rect, surf, nullptr);
                 textures.push_back(std::move(Texture(surf)));
            }
        this->row = row;
        this->col = col;
    }
}

vector<Texture> TextureSheet::Images() const{
    return textures;
}

size_t TextureSheet::Size() const{
    return textures.size();
}

Texture& TextureSheet::Get(int col, int row){
    return textures.at(row*this->row+col);
}

void TextureSheet::Scale(float sx, float sy){
    for(int i=0;i<textures.size();i++)
        textures[i].Scale(sx, sy);
}

bool TextureSheet::Valid() const{
    return !textures.empty() && col && row;
}

int TextureSheet::SoloWidth() const{
    return per_w;
}

int TextureSheet::SoloHeight() const{
    return per_h;
}

int TextureSheet::Width() const{
    return per_w*col;
}

int TextureSheet::Height() const{
    return per_h*row;
}

void TextureSheet::Draw(float x, float y, int c, int r){
    Get(c, r).Draw(x, y);
}
