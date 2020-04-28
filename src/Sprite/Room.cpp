#include "Sprite/Room.hpp"

Room::Room(){
    name = "Room";
}

void Room::update() {
    for(Wall* wall : walls)
        wall->Update();
}

void Room::draw() {}
