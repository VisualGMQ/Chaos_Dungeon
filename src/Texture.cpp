#include "Texture.hpp"

_texture::_texture():refcount(0),texture(nullptr){}

_texture::_texture(string filename):refcount(0){
    texture = IMG_LoadTexture(Director::GetInstance()->GetRender(), filename.c_str());
    if(!texture){
        cerr<<filename<<" can't load"<<endl;
    }else{
        Gain();
    }
}

_texture::_texture(SDL_Texture* tex):refcount(0){
    if(tex==nullptr)
        cerr<<"_texture construct failed, param is nullptr"<<endl;
    else{
        texture = tex;
        Gain();
    }
}

void _texture::Gain(){
    refcount++;
}

void _texture::Release(){
    refcount--;
    if(refcount==0 && texture){
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
}

int _texture::GetRefcount() const{
    return refcount;
}

Texture Texture::NullTexture;

Texture::Texture():texture(nullptr){}

Texture::Texture(string filename){
    Load(filename);
}

Texture::Texture(const Texture& t){
    texture = t.texture;
    texture->Gain();
}

void Texture::Load(string filename){
    if(texture)
        texture->Release();
    texture = new _texture(filename);
}

bool Texture::Valid() const{
    return texture;
}

int Texture::Width(){
    int w;
    SDL_QueryTexture(texture->texture, nullptr, nullptr, &w, nullptr);
    return w;
}

int Texture::Height(){
    int h;
    SDL_QueryTexture(texture->texture, nullptr, nullptr, nullptr, &h);
    return h;
}

SDL_Texture* Texture::GetTexture(){
    return texture->texture;
}

int Texture::GetRefcount() const{
    return texture->GetRefcount();
}

Texture& Texture::operator=(const Texture t){
    texture = t.texture;
    texture->Gain();
}

Texture::~Texture(){
    if(texture!=nullptr)
        texture->Release();
}

TextureSheet TextureSheet::NullSheet;

TextureSheet::TextureSheet():col(0),row(0),per_w(0),per_h(0){}

TextureSheet::TextureSheet(string filename, int c, int r){
    Load(filename, c, r);
}

void TextureSheet::Load(string filename, int c, int r){
    texture.Load(filename);
    col = c;
    row = r;
    per_w = texture.Width()/col;
    if(col==0)
        per_w = 0;
    per_h = texture.Height()/row;
    if(row==0)
        per_h = 0;
}

bool TextureSheet::Valid() const{
    return col!=0&&row!=0&&per_w!=0&&per_h!=0&&texture.Valid();
}

int TextureSheet::TotleWidth(){
    return texture.Width();
}

int TextureSheet::TotleHeight(){
    return texture.Height();
}

int TextureSheet::Width(){
    return per_w;
}

int TextureSheet::Height(){
    return per_h;
}

int TextureSheet::Col() const{
    return col;
}

int TextureSheet::Row() const{
    return row;
}

SDL_Rect TextureSheet::Get(int c, int r) const{
    if(c>col || c<0 || r>row || r<0)
        return {0, 0, 0, 0};
    return {per_w*c, per_h*r, per_w, per_h};
}

Texture& TextureSheet::GetTexture(){
    return texture;
}
