#include "Camera.hpp"

void Camera::Move(float dx, float dy){
    position.x += dx;
    position.y += dy;
}

void Camera::MoveTo(float x, float y){
    position.Set(x, y);
}

void Camera::Update(){
    glm::mat4 mat = glm::mat4(1.0);
    mat = glm::translate(mat, glm::vec3(position.x, position.y, 0));
    Program::GetInstance().UniformMat4("Camera", mat);
}
