#ifndef COLLISYSTEM_HPP
#define COLLISYSTEM_HPP
#include "Colliable.hpp"
#include "Collision.hpp"
#include "Sprite/DamageableSprite.hpp"
#include <vector>
using namespace std;

class ColliSystem{
public:
    static ColliSystem& GetInstance();
    ColliSystem() = default;
    void Clear();
    void ClearColliable();
    void ClearDamageable();
    void AddColliable(ColliableSprite* cs);
    void AddDamageable(DamageableSprite* ds);
    void Update();  /** 处理碰撞检测 */
private:
    static ColliSystem instance;
    vector<DamageableSprite*> dmgSprites;
    vector<ColliableSprite*> colliSprites;
};

#endif
