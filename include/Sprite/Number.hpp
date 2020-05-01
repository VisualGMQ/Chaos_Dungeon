#ifndef NUMBER_HPP
#define NUMBER_HPP
#include "TextureSheet.hpp"
#include "GameObject.hpp"
#include <list>
using namespace std;

class Number : public GameObject{
public:
    Number();
    Number(int num);
    void Scale(float sx, float sy);
private:
    void parseNum();
    void update() override;
    void draw() override;
    TextureSheet ts;
    int num;
    list<Texture*> num_texes;
    Size size;
};

#endif
