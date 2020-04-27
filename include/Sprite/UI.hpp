#ifndef UI_HPP
#define UI_HPP
#include "Texture.hpp"
#include "TextureSheet.hpp"

class HpBar{
public:
    HpBar();
    HpBar(int num);
    void Update();
    void SetHp(int num);
private:
    int hp;
};

class UIManager{
public:
    UIManager();
    void Update();
private:
};

#endif
