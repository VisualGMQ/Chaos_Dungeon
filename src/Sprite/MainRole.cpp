#include "Sprite/MainRole.hpp"

MainRole::MainRole():state(MainRole::State::STAND),draw_obj(&tex_stand){
}

void MainRole::Init() {
    tex_stand.Load("resources/mainrole_stand.png");
    tex_stand.Scale(10, 10);
    TextureSheet ts("resources/mainrole_walk.png", 2, 1);
    ani_walk.Load(ts, {4, 4});
    ani_walk.Scale(10, 10);
}

void MainRole::EventHandle(SDL_Event& event) {}

void MainRole::update() {
    Director* director = Director::GetInstance();
    const float speed = 10;
    SET_STATE(state, State::STAND);
    if(director->KeyState(SDLK_w)==KeyState::PRESSING){
        position.y += speed;
        SET_STATE(state, State::WALK);
    }
    if(director->KeyState(SDLK_a)==KeyState::PRESSING){
        position.x -= speed;
        SET_STATE(state, State::WALK);
    }
    if(director->KeyState(SDLK_s)==KeyState::PRESSING){
        position.y -= speed;
        SET_STATE(state, State::WALK);
    }
    if(director->KeyState(SDLK_d)==KeyState::PRESSING){
        position.x += speed;
        SET_STATE(state, State::WALK);
    }
    if(HAS_STATE(state, State::WALK)){
        ani_walk.Play();
        draw_obj = &ani_walk;
    }else{
        ani_walk.Stop();
        draw_obj = &tex_stand;
    }       
}

void MainRole::draw() {
    ani_walk.Update();
    draw_obj->Draw(Position().x, Position().y);
}
