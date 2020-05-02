#include "Sprite/RushMan.hpp"

RunMan::RunMan(){
    tex_stand.Load("resources/enemy3_stand.png");
    tex_stand.Scale(3, 3);
    tex_die.Load("resources/enemy3_die.png");
    tex_stand.Scale(3, 3);
    TextureSheet ts("resources/enemy3_walk.png", 2, 1);
    ani_walk.Load(ts, {3, 3});
    ani_walk.Scale(3, 3);
    ts.Load("resources/enemy3_rush.png", 2, 1);
    ani_rush.Load(ts, {2, 2});
    ani_rush.Scale(3, 3);
    ts.Load("resources/enemy3_lift.png", 2, 1);
    ani_throw.Load(ts, {2, 2});
}

void RunMan::Init(){}

void RunMan::update(){}
void RunMan::draw(){}
void RunMan::alive_logic(){}
void RunMan::die_logic(){}
