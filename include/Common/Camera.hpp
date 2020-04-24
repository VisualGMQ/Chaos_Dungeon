#ifndef CAMERA_HPP
#define CAMERA_HPP
#include "Director.hpp"

class Camera{
public:
    Camera() = default;
    void Move(float dx, float dy);
    void MoveTo(float x, float y);
    void Update();
private:
    Vec position;
};

#endif
