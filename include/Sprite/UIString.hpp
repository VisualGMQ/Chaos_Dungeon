#ifndef UISPRITE_HPP
#define UISPRITE_HPP
#include "TextureSheet.hpp"
#include "GameObject.hpp"
#include <string>
using namespace std;

/**
 * @brief 表示英文字符
 * @warn 不管给如的字符大小写，绘制的一律大写
 */
class UIString : public GameObject{
public:
    static UIString* Create();
    void SetText(string t);
    string GetText() const;
    void Scale(float sx, float sy);
private:
    void draw() override;
    void update() override;
    UIString();
    TextureSheet ts;
    string text;
};

#endif
