#ifndef SPRITE_HPP
#define SPRITE_HPP
#include "Texture.hpp"
#include "TextureSheet.hpp"
#include "Animation.hpp"
#include "Director.hpp"
#include "Colliable.hpp"
#include "HelpFunc.hpp"
#include <list>
#include <string>
using namespace std;

/**
 * @brief 这个宏需要使用在所有Sprite的非抽象子类中。用于定义一些公共的接口和数据。
 * @warning 不要忘记在类体外初始化 instances 静态变量
 */
#define DEFINE_DELETEINTERFACE(classname) \
    public:\
    static classname* Create() {\
        classname* instance = new classname;\
        instance->Init();\
        instances.push_back(instance);\
        return instance;\
    }\
    static void DeleteInstance(unsigned int id){\
        willdel_list.push_back(id);\
    }\
    void DeleteSelf() override{\
        DeleteInstance(id);\
    }\
    private:\
    static list<classname*> instances;\
    static list<unsigned int> willdel_list;

#define DEFINE_DELETEBODY(classname)\
    public:\
    static void Delete(){\
        while(!willdel_list.empty()){\
            unsigned int id = willdel_list.back();\
            willdel_list.pop_back();\
            for(auto i=instances.begin();i!=instances.end();i++){\
                if((*i)->GetID()==id){\
                    delete *i;\
                    instances.erase(i);\
                    break;\
                }\
            }\
        }\
    }

class Sprite{
    public:
        virtual void Init() = 0;
        void Show(); /** @warn 显示精灵，必须在Update里面实现对isshow变量的反馈*/
        void Hide(); /** @warn 隐藏精灵，必须在Update里面实现对isshow变量的反馈*/
        bool IsShow() const;
        virtual Vec Position() const;
        virtual void Move(float dx, float dy);
        virtual void MoveTo(float x, float y);
        Vec TopLeft() const;
        unsigned int GetID() const;
        /**
         * @brief 这个函数让对象可以自己析构自己
         */
        virtual void DeleteSelf() = 0;
        /**
         * @brief 事件处理，在这里实现你人物的事件处理
         */
        virtual void EventHandle(SDL_Event& event) = 0;
        /**
         * @brief 精灵更新，每一帧需要调用一次
         */
        void Update();
    protected:
        Sprite();   /** 构造函数不给出，子类应当创建自己的工厂方法 */
        static unsigned int Current_ID;
        //在这里实现你的逻辑
        virtual void update() = 0;
        //在这里实现你的绘制
        virtual void draw() = 0;
        Vec position;
        bool isshow;
        unsigned int id;
};

/**
 * @brief 可以进行碰撞检测的精灵
 */
class ColliableSprite : public Sprite, public Colliable{
    public:
        void Move(float dx, float dy) override;
        void MoveTo(float x, float y) override;
        virtual Vec Position() const override;
        void update() override; 
    protected:
        ColliableSprite() = default;
};

/**
 * @brief 静态的不参与碰撞的贴图
 */
class StaticSprite: public Sprite{
    DEFINE_DELETEINTERFACE(StaticSprite)
    DEFINE_DELETEBODY(StaticSprite)
public:
    void Init() override;
    void Load(string filename);
    void EventHandle(SDL_Event& event) override;
protected:
    StaticSprite() = default;
private:
    Texture texture;
    void update() override;
    void draw() override;
};

#endif
