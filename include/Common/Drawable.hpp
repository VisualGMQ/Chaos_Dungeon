#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

enum FlipFlag{
    NONE = 0x00,
    VERTICAL = 0x01,
    HORIZENTAL = 0x02
};

class Drawable{
public:
    Drawable() = default;
    virtual void Draw(float x, float y, float degree = 0, FlipFlag flag = FlipFlag::NONE) = 0;
};

#endif
