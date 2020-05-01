#ifndef NUMBER_HPP
#define NUMBER_HPP
#include "TextureSheet.hpp"
#include "GameObject.hpp"
#include <list>
using namespace std;

/**
 * @brief 表示整数数字（暂时不支持负数）
 * @warn 不支持负数
 */
class Number : public GameObject{
public:
    static Number* Create();
    void Scale(float sx, float sy);
    void SetNum(int num);
    Size GetSize() const;
    Size SoloSize() const;
    int GetNum() const;
private:
    Number();
    void parseNum();
    void update() override;
    void draw() override;
    TextureSheet ts;
    int num;
    Size size;
    list<int> num_texes;
};

#endif
