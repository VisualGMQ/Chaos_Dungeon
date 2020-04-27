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
#include <list>
using namespace std;

class MainRole;
class Wall;
class LittleRobo;

/**
 * @brief 用于记录世界中所有的东西
 *
 * 只能够记录Sprite类和其子类
 *
 * @warn 对于ColliSprite和DamageableSprite，比如传入分配在堆上的指针。在调用Clear方法或WorldModel的析构函数的时候会自行释放内存空间。
 */
class WorldModel{
public:
    static WorldModel* GetInstance();
    static void Destroy();
    void Init();
    void AddColliable(ColliableSprite* sp);
    void AddDmgable(DamageableSprite* sp);
    void AddSprite(Sprite* sp);
    void ClearColliable();
    void ClearDmgable();
    void ClearSprite();
    void DeleteElem(unsigned int id);
    void Clear();
    MainRole* GetMainRole();
    void EventHandle(SDL_Event& event);
    void Update();
    ~WorldModel();
private:
    void realDelete();
    static list<unsigned int> willdel_list;
    static WorldModel* instance;
    list<ColliableSprite*> colliSp;
    list<DamageableSprite*> dmgSp;
    list<Sprite*> sprites;
    MainRole* role;
};

#endif
