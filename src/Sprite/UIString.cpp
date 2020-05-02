#include "Sprite/UIString.hpp"

UIString* UIString::Create(){
    return new UIString;
}

UIString::UIString(){
    name = "UIString";
    ts.Load("resources/chars.png", 26, 1);
}

void UIString::SetText(string t){
    text = t;
}

string UIString::GetText() const{
    return text;
}

void UIString::Scale(float sx, float sy){
    ts.Scale(sx, sy);
}

void UIString::update(){}

void UIString::draw(){
    int w = ts.SoloWidth();
    const int padding = w/3;
    int offset = 0;
    for(char i : text){
        if(i==' '){
            offset += w+padding;
            continue;
        }
        if(i<='Z' && i>='A' )
            i += 'z'-'Z';
        ts.Get(i-'a', 0).Draw(Position().x+offset, Position().y);
        offset += w+padding;
    }
}
