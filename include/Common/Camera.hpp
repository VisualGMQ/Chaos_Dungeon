#ifndef CAMERA_HPP
#define CAMERA_HPP
#include "Director.hpp"

class Camera{
public:
    static Camera* GetInstance();
    static void Destroy();
    void Move(float dx, float dy);
    void MoveTo(float x, float y);
    void Update();
private:
    Camera() = default;
    static Camera* camera;
    Vec position;
};

#endif
