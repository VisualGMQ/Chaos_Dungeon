#include "Sprite/Number.hpp"

Number* Number::Create(){
    return new Number;
}

void Number::SetNum(int num){
    this->num = num;
    parseNum();
}

int Number::GetNum() const{
    return num;
}

Number::Number():num(0){
    ts.Load("resources/numbers.png", 10, 1);
}

Size Number::GetSize() const{
    return size; 
}

Size Number::SoloSize() const{
    Size size;
    size.w = ts.SoloWidth();
    size.h = ts.SoloHeight();
    return size;
}

void Number::parseNum(){
    num_texes.clear();
    int n = num;
    if(n==0){
        num_texes.push_back(0);
        return;
    }
    while(n!=0){
        int s = n%10;
        num_texes.push_front(s);
        n /= 10;
    }
}

void Number::update() {}

void Number::Scale(float sx, float sy){
    ts.Scale(sx, sy);
}

void Number::draw() {
    const int padding = ts.SoloWidth()/3;
    const int w = ts.SoloWidth();
    int i = 0;
    size.w = 0;
    size.h = w;
    for(auto it=num_texes.begin();it!=num_texes.end();it++){
        ts.Get((*it), 0).Draw(Position().x+(padding+w)*i, Position().y);
        size.w += padding+w;
        i++;
    }
}
