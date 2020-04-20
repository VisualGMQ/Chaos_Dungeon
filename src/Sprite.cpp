#include "Sprite.hpp"

ISprite::ISprite():isshow(true),degree(0),fflag(NO_FLIP),size({0, 0}){}

void ISprite::Show(){
    isshow = true;
}

void ISprite::Hide(){
    isshow = false;
}

bool ISprite::IsShown() const{
    return isshow;
}

void ISprite::SetSize(int w, int h){
    size.w = w;
    size.h = h;
}

Size ISprite::GetSize() const{
    return size;
}

void ISprite::Flip(FlipFlag flag){
    fflag |= flag; 
}

FlipFlag ISprite::GetFlipFlag() const{
    return static_cast<FlipFlag>(fflag);
}

void ISprite::Rotate(float ddeg){
    degree = ddeg;
}

void ISprite::RotateTo(float deg){
    degree = deg;
}

float ISprite::GetDegree() const{
    return degree;
}

StaticSpriteT::StaticSpriteT(string filename){
    LoadTexture(filename);
}

void StaticSpriteT::LoadTexture(string filename){
    texture.Load(filename);
}

void StaticSpriteT::Move(float dx, float dy) {
    position.x += dx;
    position.y += dy;
}

void StaticSpriteT::MoveTo(float x, float y) {
    position.Set(x, y);
}

void StaticSpriteT::Draw() {
    if(IsShown())
        texture.Draw(position.x, position.y, size.w, size.h, degree, static_cast<FlipFlag>(fflag));
}

void StaticSpriteT::Update(){}

StaticSpriteAT::StaticSpriteAT(Animation ani){
    animation = ani;
}

Animation& StaticSpriteAT::GetAni(){
    return animation;
}

void StaticSpriteAT::Move(float dx, float dy) {
    position.x += dx;
    position.y += dy;
}

void StaticSpriteAT::Draw() {
    if(isshow)
        animation.Draw(position.x, position.y, size.w, size.h, degree, static_cast<FlipFlag>(fflag));
}

void StaticSpriteAT::Update() {
    animation.Update();
}

void StaticSpriteAT::MoveTo(float x, float y) {
    position.Set(x, y);
}

StaticSpriteAS::StaticSpriteAS(AnimationS ani){
    SetAnimationS(ani);
}

void StaticSpriteAS::SetAnimationS(AnimationS ani){
    cout<<"setting animation"<<endl;
    animation = ani;
    cout<<"set animation"<<endl;
}

AnimationS& StaticSpriteAS::GetAni(){
    return animation;
}

void StaticSpriteAS::Move(float dx, float dy) {
    position.x += dx;
    position.y += dy;
}

void StaticSpriteAS::MoveTo(float x, float y) {
    position.Set(x, y);
}

void StaticSpriteAS::Draw() {
    if(isshow)
        animation.Draw(position.x, position.y, size.w, size.h, degree, static_cast<FlipFlag>(fflag));
}

void StaticSpriteAS::Update() {
    animation.Update();
}
