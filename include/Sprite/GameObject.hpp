#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP
#include "math.hpp"
#include <string>
#include <list>
using namespace std;
/**
 * @brief 只能用于GameObject类中，用于释放其子类实例占的内存。每当出现一个新final子类的时候就需要在JunkRecycle里面增加这个宏
 */
#define RECYCLE_FINALCLASS_BY_ITER(classname, list, iter) \
    if((*iter)->GetName()==#classname){\
        classname* instance = (classname*)(*iter);\
        delete instance;\
        list.erase(iter);\
        break;\
    }

#define RECYCLE_FINALCLASS_BY_INSTANCE(classname, list, instance) \
    if(instance->GetName()==#classname){\
        classname* ins = (classname*)(instance);\
        delete ins;\
        continue;\
    }

/**
 * @brief 表示ID的类型
 */
using IDType = unsigned int;

class GameObject{
public:
    static void ClearAllObject();
    static void DeleteObject(IDType del_id);
    GameObject();
    virtual void Move(float dx, float dy);
    virtual void MoveTo(float x, float y);
    virtual Vec Position() const;
    void Show();
    bool IsShow() const;
    void Hide();
    string GetName() const;
    virtual void DeleteSelf();
    virtual void Update();
    IDType GetID() const;
    static list<unsigned int> _willdel_list;    /** 为了防止循环头文件包含而放到外部，你绝不该使用 */
    static list<GameObject*> _objects;    /** 为了防止循环头文件包含而放到外部，你绝不该使用 */
    static bool _delete_all;    /** 为了防止循环头文件包含而放到外部，你绝不该使用 */
protected:
    virtual void update() = 0;
    virtual void draw() = 0;
    string name;    /** 记录类的名称，只读的，在继承创建新类的时候必须在构造函数中改为新的名称 */
    Vec position;
    bool isshow;
    IDType id;
private:
    static IDType cur_id;
};

#endif
