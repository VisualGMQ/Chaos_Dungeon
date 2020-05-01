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
    initCursor();
    WorldModel* wm = WorldModel::GetInstance();
    
    //初始化一些层
    /* main层存放最后面的背景
     * itemc层存放一些会被挡住的物体
     * object层存放人物和砖块等
     * bullet层存放子弹
     * effect层存放特效
     * ui层存放最前面的ui物件
    */
    wm->CreateLayer("item");
    wm->CreateLayer("object", true);
    wm->CreateLayer("effect");
    wm->CreateLayer("bullet");
    wm->CreateLayer("ui");


    Director* director = Director::GetInstance();
    MainRole* mainrole = MainRole::GetRole();

    //add mainrole
    mainrole->MoveTo(director->Width()/2, 100);
    wm->AddGameObject("object", mainrole);

    //add hpbar
    HpBar* hpbar = HpBar::GetInstance();
    hpbar->MoveTo(50, director->Height()-20);
    wm->AddGameObject("ui", hpbar);
    hpbar->SetHp(mainrole->prop.hp);

    int col = director->Width()/32*3,
        row = director->Height()/32*3;
    for(int i=0;i<col;i++) {
        Wall* w = Wall::Create();
        w->MoveTo(i*w->Width(), 0);
        wm->AddGameObject("object", w);
        Wall* w2 = Wall::Create();
        w2->MoveTo(i*w2->Width(), director->Height()-w->Height()); 
        wm->AddGameObject("object", w2);
    }
    for(int i=1;i<row-1;i++){
        if(i!=5){
            Wall* w = Wall::Create();
            w->MoveTo(0, i*w->Height());
            wm->AddGameObject("object", w);
            Wall* w2 = Wall::Create();
            w2->MoveTo(director->Width()-w2->Width(), i*w->Height()); 
            wm->AddGameObject("object", w2);
        }else{
            Door* door = Door::Create();
            door->MoveTo(0,i*door->Height());
            wm->AddGameObject("object", door);
            door = Door::Create();
            door->MoveTo(director->Width()-door->Width(),i*door->Height());
            wm->AddGameObject("object", door);
        }
    }
    LittleRobo* robo = LittleRobo::Create();
    robo->Init();
    robo->MoveTo(500, 500);
    wm->AddGameObject("object", robo);
    
    //Timer
    timer = Timer::Create();
    timer->Scale(5, 5);
    timer->MoveTo(300, director->Height()-20);
    WorldModel::GetInstance()->AddGameObject("ui", timer);

    //KilledEnemyNum
    KilledEnemyNum_Sington* kilennum = KilledEnemyNum_Sington::GetInstance();
    kilennum->Scale(5, 5);
    kilennum->MoveTo(500, director->Height()-20);
    WorldModel::GetInstance()->AddGameObject("ui", KilledEnemyNum_Sington::GetInstance());
}

void GameBody::initCursor(){
    SDL_Surface* sur_cursor = IMG_Load("resources/cursor.png");
    cursor = SDL_CreateColorCursor(sur_cursor, sur_cursor->w/2, sur_cursor->h/2);
    SDL_FreeSurface(sur_cursor);
    SDL_SetCursor(cursor);
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
    static int time_count = 0;
    static int enemy_num = 1;
    if(time_count<100)
        time_count++;
    else{
        time_count = 0;
        srand(time(nullptr));
        for(int i=0;i<enemy_num;i++){
            LittleRobo* robo = LittleRobo::Create();
            robo->MoveTo(rand()%(600-0+1)+100, rand()%(400+1)+100);
            WorldModel::GetInstance()->AddGameObject("main", robo);
        }
        enemy_num++;
    }
    WorldModel::GetInstance()->Update();
    ObjJunkRecycle();
    ColliSystem::GetInstance()->Update();
}

GameBody::~GameBody(){
    SDL_FreeCursor(cursor);
    Director::Quit();
    WorldModel::Destroy();
    Camera::Destroy();
    GameObject::ClearAllObject();
    ObjJunkRecycle();
    SDL_Quit();
    TTF_Quit();
    IMG_Quit();
}
