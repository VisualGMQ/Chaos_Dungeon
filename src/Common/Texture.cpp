#include "Texture.hpp"

Texture::Texture():surface(nullptr),texid(0){}

Texture::Texture(SDL_Surface* surface):Texture(){
    Load(surface);
}

Texture::Texture(const Texture& t):Texture(){
    *this = t;
}

Texture::Texture(string filename):Texture(){
    Load(filename);
}

void Texture::Load(SDL_Surface* surf){
    if(surface)
        releaseSurface();
    surface = surf;
    if(surface){
        configTexture();
    }   
}

Texture Texture::Copy(){
    return Texture(SDL_DuplicateSurface(surface));
}

void Texture::Load(string filename){
    if(surface){
        releaseSurface();
    }
    surface = IMG_Load(filename.c_str());
    if(!surface){
        cerr<<filename<<" load failed"<<endl;
        return;
    }
    if(!surface){
        cerr<<"convert surface to RGBA8888 failed"<<endl;
        return;
    }
    configTexture();
}

void Texture::Scale(float sx, float sy){
    if(sx<=0||sy<=0){
        cerr<<"can't scale to 0"<<endl;
        return;
    }
    size.w *= sx;
    size.h *= sy;
}

void Texture::configTexture(){
    if(!surface)
        return ;
    if(texid)
        glDeleteTextures(1, &texid);
    glGenTextures(1, &texid);
    glBindTexture(GL_TEXTURE_2D, texid);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    GLenum format = GL_RGBA;
    switch(surface->format->format){
        case SDL_PIXELFORMAT_RGB888:
            format = GL_RGB;
            break;
        case SDL_PIXELFORMAT_RGBA8888:
            format = GL_RGBA;
            break;
        case SDL_PIXELFORMAT_BGR888:
            format = GL_BGR;
            break;
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, GL_FALSE, format, GL_UNSIGNED_BYTE, (unsigned char*)surface->pixels);
    glGenerateMipmap(GL_TEXTURE_2D);
    size.w = surface->w;
    size.h = surface->h;
}

Texture& Texture::operator=(const Texture& t){
    surface = t.surface;
    gainSurface();
    configTexture();
    return *this;
}

void Texture::gainSurface(){
    if(surface)
        surface->refcount++;
}

void Texture::releaseSurface(){
    if(surface){
        surface->refcount--;
        if(surface->refcount==0)
            SDL_FreeSurface(surface);
    }
}

size_t Texture::Refcount() const{
    return surface?surface->refcount:0;
}

int Texture::Width() const{
    return size.w;
}

int Texture::Height() const{
    return size.h;
}

void Texture::Width(int w){
    size.w = w;
}

void Texture::Height(int h){
    size.h = h;
}

void Texture::Draw(float x, float y){
    SDL_FPoint pos[4] = {
        {x+size.w/2, y-size.h/2},
        {x-size.w/2, y-size.h/2},
        {x+size.w/2, y+size.h/2},
        {x-size.w/2, y+size.h/2}
    };
    for(int i=0;i<4;i++){
        pos[i].x = pos[i].x/Director::GetInstance()->Width() - 0.5;
        pos[i].y = pos[i].y/Director::GetInstance()->Height() - 0.5;
    }
    float texcoord[8] = {
        1, 1,
        0, 1,
        1, 0,
        0, 0
    };
    GLuint VBO, TBO, EBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(pos), pos, GL_STATIC_DRAW);
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(SDL_FPoint), (void*)0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &TBO);
    glBindBuffer(GL_ARRAY_BUFFER, TBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texcoord), texcoord, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float)*2, (void*)0);
    glEnableVertexAttribArray(1);

    int indices[6] = {0, 1, 2,
        1, 2, 3};
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glBindTexture(GL_TEXTURE_2D, texid);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(1, &VAO);
}

bool Texture::Valid() const{
    return surface;
}

Texture::~Texture(){
    releaseSurface();
    glDeleteTextures(1, &texid);
}
