#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

class Drawable{
public:
    Drawable() = default;
    virtual void Draw(float x, float y) = 0;
};

#endif
