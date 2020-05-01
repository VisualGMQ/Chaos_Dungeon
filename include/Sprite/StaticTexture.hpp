#ifndef STATICTEXTURE_HPP
#define STATICTEXTURE_HPP
#include "GameObject.hpp"
#include "Texture.hpp"
#include <string>
using namespace std;

class StaticTexture : public GameObject{
public:
    static StaticTexture* Create();
    void Load(string filename);
    void Scale(float sx, float sy);
private:
    void update() override;
    void draw() override;
    StaticTexture();
    Texture texture;
};

#endif
