#include "GameBody/GameBody.hpp"

GameBody::GameBody(){
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG);
    TTF_Init();
    const int WindowWidth = 1200, WindowHeight = 800;
    SDL_Window* window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WindowWidth, WindowHeight, SDL_WINDOW_SHOWN|SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);
    if(!window){
        cerr<<"window can't create"<<endl;
    }
    SDL_GL_CreateContext(window);
    if(glewInit()!=GLEW_OK){
        cerr<<"glew init failed"<<endl;
    }
    Director::Init(window, WindowWidth, WindowHeight, 30);
    WorldModel::GetInstance()->Init();
    init();
}

void GameBody::init(){
    WorldModel* wm = WorldModel::GetInstance();
    LittleRobo* robo = LittleRobo::Create();
    robo->Show();
    robo->MoveTo(300, 300);
    wm->AddDmgable(robo);
    Wall* wall = Wall::Create();
    wall->Show();
    wall->MoveTo(400, 400);
    wm->AddColliable(wall);
}

void GameBody::Update(){
    Director* direct = Director::GetInstance();
    SDL_Event& event = direct->GetEvent();
    glEnable(GL_DEPTH_TEST|GL_BLEND);
    while(!direct->IsQuit()){
        glClearColor(0.1, 0.1, 0.1, 0.1);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        Program::GetInstance().Use();
        Camera::GetInstance()->Update();
        Director::GetInstance()->Update();
        while(SDL_PollEvent(&event)){
            direct->EventHandle();
            if(event.type==SDL_QUIT)
                direct->Exit();
            if(event.type==SDL_WINDOWEVENT){
                if(event.window.event==SDL_WINDOWEVENT_RESIZED)
                    Director::GetInstance()->SizeAdapt(event.window.data1, event.window.data2);
            }
            WorldModel::GetInstance()->EventHandle(event);
        }
        step();
        SDL_GL_SwapWindow(direct->GetWindow());
        SDL_Delay(1000.0/direct->fps);
    }
}

void GameBody::step(){
    ColliSystem::GetInstance()->Update();
    WorldModel::GetInstance()->Update();
}

GameBody::~GameBody(){
    Director::Quit();
    WorldModel::Destroy();
    Camera::Destroy();
    SDL_Quit();
    TTF_Quit();
    IMG_Quit();
}
