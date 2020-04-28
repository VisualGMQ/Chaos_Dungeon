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
    init();
}

void GameBody::init(){
    WorldModel* wm = WorldModel::GetInstance();
    Director* director = Director::GetInstance();
    MainRole* mainrole = MainRole::Create();
    mainrole->MoveTo(director->Width()/2, 100);
    wm->AddGameObject(mainrole);
    int col = director->Width()/32*3,
        row = director->Height()/32*3;
    for(int i=0;i<col;i++) {
        Wall* w = Wall::Create();
        w->MoveTo(i*w->Width(), 0);
        wm->AddGameObject(w);
        Wall* w2 = Wall::Create();
        w2->MoveTo(i*w2->Width(), director->Height()-w->Height()); 
        wm->AddGameObject(w2);
    }
    for(int i=1;i<row-1;i++){
        if(i!=5){
            Wall* w = Wall::Create();
            w->MoveTo(0, i*w->Height());
            wm->AddGameObject(w);
            Wall* w2 = Wall::Create();
            w2->MoveTo(director->Width()-w2->Width(), i*w->Height()); 
            wm->AddGameObject(w2);
        }else{
            Door* door = Door::Create();
            door->MoveTo(0,i*door->Height());
            wm->AddGameObject(door);
            door = Door::Create();
            door->MoveTo(director->Width()-door->Width(),i*door->Height());
            wm->AddGameObject(door);
        }
    }
    LittleRobo* robo = LittleRobo::Create();
    robo->Init();
    robo->MoveTo(500, 500);
    wm->AddGameObject(robo);
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
                if(event.window.event==SDL_WINDOWEVENT_RESIZED){
                    direct->SizeAdapt(event.window.data1, event.window.data2);
                }
            }
        }
        step();
        SDL_GL_SwapWindow(direct->GetWindow());
        SDL_Delay(1000.0/direct->fps);
    }
}

void GameBody::step(){
    WorldModel::GetInstance()->Update();
    ObjJunkRecycle();
    ColliSystem::GetInstance()->Update();
}

GameBody::~GameBody(){
    Director::Quit();
    WorldModel::Destroy();
    Camera::Destroy();
    GameObject::ClearAllObject();
    ObjJunkRecycle();
    SDL_Quit();
    TTF_Quit();
    IMG_Quit();
}
