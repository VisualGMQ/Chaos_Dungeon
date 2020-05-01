#ifndef WORLDMODEL_HPP
#define WORLDMODEL_HPP
#include "Texture.hpp"
#include "TextureSheet.hpp"
#include "Animation.hpp"
#include "Sprite.hpp"
#include "Bullet.hpp"
#include "ColliSystem.hpp"
#include "Sprite/MainRole.hpp"
#include "Sprite/Wall.hpp"
#include "Sprite/LittleRobo.hpp"
#include "Sprite/Bullet.hpp"
#include <algorithm>
#include <list>
using namespace std;

class MainRole;
class Wall;
class LittleRobo;

/**
 * @brief 层，物体可以存储在层中
 * @warn 层在调用析构函数的时候会将内部的物体全部释放内存，所以如果有不想要释放的物体请提前使用TakeAway拿出
 */
class Layer{
public:
    Layer() = default;
    Layer(string name);
    void AddGameObject(GameObject* obj);
    void RemoveObject(IDType id);
    void Clear();
    void TakeAway(IDType id);
    void TakeAwayAll();
    void JunkRecycle();
    string GetName() const;
    void SetName(string n);
    list<GameObject*> objs;
    void Update();
    void EnableOrder();
    void DisableOrder();
    bool IsOrderDraw() const;
    ~Layer();
private:
    void takeAwayRecycle();
    void removeRecycle();
    list<IDType> will_remove;
    list<IDType> will_takeaway;
    string name;    /** 层的名称 */
    bool isorder;   /** 指定层是否会按照物体的y坐标排序绘制 */
};

/**
 * @brief 用于记录世界中所有的东西(按层记)。在创建的时候默认会有一个名字为main的层
 *
 * 只能够记录Sprite类和其子类
 *
 * @warn 对于ColliSprite和DamageableSprite，比如传入分配在堆上的指针。在调用Clear方法或WorldModel的析构函数的时候会自行释放内存空间。
 */
class WorldModel{
public:
    static WorldModel* GetInstance();
    static void Destroy();
    void AddGameObject(string layer, GameObject* obj);
    void DeleteElem(string layer, IDType id);
    void DeleteElem(IDType id);
    void TakeAway(string layer, IDType id);
    void TakeAway(IDType id);
    Layer* GetLayer(string name);
    int GetLayerIdx(string name) const;
    Layer* CreateLayer(string name, bool isorder = false);
    bool ExistsLayer(string name);
    void Clear();    /** 清除所有的层中的物体并释放内存 */
    void TakeAwayAll();  /** 清除所有层中的物体，不释放内存 */
    void ClearWorldModel(); /** 清除所有层并释放内存 */
    void DeleteLayer(string name);
    void TakeAwayLayer(string name);
    void MoveLayer(string name, int pos);
    void Update();
    ~WorldModel();
private:
    WorldModel();
    void junkRecycle();
    static list<string> willdel_list;
    static list<string> will_takeaway;
    static WorldModel* instance;
    static bool clear_all;
    list<Layer*> layers;
};

#endif
