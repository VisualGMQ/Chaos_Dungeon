#include "Sprite/StaticTexture.hpp"

StaticTexture* StaticTexture::Create(){
    return new StaticTexture;
}

StaticTexture::StaticTexture(){
    name = "StaticTexture";
}

void StaticTexture::Load(string filename){
    texture.Load(filename);
}

void StaticTexture::Scale(float sx, float sy){
    texture.Scale(sx, sy);
}

void StaticTexture::update() {}

void StaticTexture::draw() {
    texture.Draw(Position().x, Position().y);
}
