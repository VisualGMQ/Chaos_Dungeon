#include "Sprite/Door.hpp"

Door* Door::Create(){
    Door* door = new Door;
    door->Init();
    return door;
}

Door::Door(){
    name = "Door";
    TextureSheet ts_open("resources/door_open.png", 4, 1);
    ts_open.Scale(3, 3);
    ani_open.Load(ts_open, {2, 2, 2, 2});
    TextureSheet ts_close("resources/door_close.png", 4, 1);
    ts_close.Scale(3, 3);
    ani_close.Load(ts_close, {2, 2, 2, 2});
    tex_close = ts_close.Get(3, 0);
    tex_open = ts_open.Get(3, 0);
    colliobj.AttachLayer(ColliLayer::BLOCK);
    ColliSystem::GetInstance()->AddColliable(this);
    colliobj.physic_info.m = 0;

}

void Door::Init() {
    Close();
    int w = ani_close.CurrentFrame().texture.Width(),
        h = ani_close.CurrentFrame().texture.Height();
    Close();
    colliobj.Set(AABB(Position().x-w/2, Position().y-h/2, w, h));
}

int Door::Width() const{
    return tex_close.Width();
}

int Door::Height() const{
    return tex_close.Height();
}

void Door::Open(){
    state = OPEN;
    colliobj.UnsetColliType(ColliType::SOLIDABLE);
    ani_open.Play();
}

void Door::Close(){
    state = CLOSE;
    colliobj.AttachColliType(ColliType::SOLIDABLE);
    ani_close.Play();
}

void Door::update(){
    ColliableSprite::update();
    ani_open.Update();
    ani_close.Update();
    if(state==OPEN){
        if(ani_open.State()==AniPlayState::PLAYING)
            draw_ptr = &ani_open;
        else
            draw_ptr = &tex_open;
    }
    if(state==CLOSE){
        if(ani_close.State()==AniPlayState::PLAYING)
            draw_ptr = &ani_close;
        else
            draw_ptr = &tex_close;
    }
}

void Door::draw() {
    draw_ptr->Draw(Position().x, Position().y);
}

Door::~Door(){
    ColliSystem::GetInstance()->DeleteElem(GetID());
}
