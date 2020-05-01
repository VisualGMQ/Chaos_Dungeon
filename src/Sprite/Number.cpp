#include "Sprite/Number.hpp"

Number::Number():num(0){
    ts.Load("resources/numbers.png", 10, 1);
    size.w = ts.SoloWidth();
    size.h = ts.SoloHeight();
}

Number::Number(int num):Number(){
    this->num = num;
}

void Number::parseNum(){
    int n = num;
    while(num!=0){
        int s = num%10;
        num_texes.push_front(&ts.Get(s, 0));
        num /= 10;
    }
}

void Number::update() {}

void Number::Scale(float sx, float sy){
    size.w *= sx;
    size.h *= sy;
}

void Number::draw() {
    const int padding = size.w/3;
    for(auto it=num_texes.begin();it!=num_texes.end();it++){
        (*it)->Draw(Position().x, Position().y);
    }
}
