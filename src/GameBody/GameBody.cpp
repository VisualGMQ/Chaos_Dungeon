#include "GameBody/GameBody.hpp"

GameBody::GameBody(){
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG);
    TTF_Init();
    SDL_Window* window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN|SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);
    if(!window){
        cerr<<"window can't create"<<endl;
    }
    SDL_GL_CreateContext(window);
    if(glewInit()!=GLEW_OK){
        cerr<<"glew init failed"<<endl;
    }
    Director::Init(window, 800, 600, 30);

    texture.Load("resources/monster1_stand.png");
    texture.Scale(10, 10);
    sheet.Load("resources/monster1_walk.png", 2, 1);
    ani.Load(sheet, {3, 3});
    ani.Play();
    ani.Scale(10, 10);
    ani.EnableLoop();
}

void GameBody::Update(){
    Director* direct = Director::GetInstance();
    SDL_Event& event = direct->GetEvent();
    glEnable(GL_DEPTH_TEST|GL_BLEND);
    while(!direct->IsQuit()){
        glClearColor(0.1, 0.1, 0.1, 0.1);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        while(SDL_PollEvent(&event)){
            if(event.type==SDL_QUIT)
                direct->Exit();
            if(event.type==SDL_WINDOWEVENT){
                if(event.window.event==SDL_WINDOWEVENT_RESIZED)
                    Director::GetInstance()->SizeAdapt(event.window.data1, event.window.data2);
            }
            eventHandle();
        }
        Program::GetInstance().Use();
        Director::GetInstance()->Update();
        step();
        SDL_GL_SwapWindow(direct->GetWindow());
        SDL_Delay(1000.0/direct->fps);
    }
}

void GameBody::eventHandle(){
}

void GameBody::step(){
    ani.Update();
    texture.Draw(100, 100);
    for(int i=0;i<sheet.Size();i++){
        Texture tex = sheet.Get(i, 0).Copy();
        tex.Scale(10, 10);
        tex.Draw(i*200, 100);
    }       
    ani.CurrentFrame().texture.Draw(400, 400);
}

GameBody::~GameBody(){
    Director::Quit();
    SDL_Quit();
    TTF_Quit();
    IMG_Quit();
}
