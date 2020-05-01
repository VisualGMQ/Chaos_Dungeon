#ifndef COLLISION_HPP
#define COLLISION_HPP
#include "math.hpp"
#include "Sprite/BasicProp.hpp"
#include "HelpFunc.hpp"
/* 迭代碰撞的次数 */
#define RETRIVE_COLLI_NUM 8
using namespace std;

struct AABB{
    AABB() = default;
    AABB(float x, float y, float w, float h);
    AABB(Vec tl, Vec br);
    Vec Center() const;
    void MoveTo(float x, float y);
    void Move(float dx, float dy);
    float Width() const;
    float Height() const;
    Vec tl; /** @warn 这个tl是在SDL原本坐标下的tl*/
    Vec br; /** @warn 这个br是在SDL原本坐标系下的br*/
};

ostream& operator<<(ostream& o, const AABB& aabb);

struct OBB{
    OBB() = default;
    OBB(Vec cent, float w_2, float h_2, float degree);
    void GetPoints(Vec points[4]);
    Vec center;
    Rot2D rotation;
    float half_w;
    float half_h;
};

ostream& operator<<(ostream& o, const OBB& obb);

struct Circle{
    Circle();
    Circle(float cx, float cy, float r);
    Vec center;
    float radius;
};

ostream& operator<<(ostream& o, const Circle& circle);

enum class ObjType{
    OBJ_TYPE_UNKNOWN = 0,
    CIRCLE = 1,
    AABB = 2,
    OBB = 3
};

enum ColliType{
    COLLI_TYPE_UNKNOWN = 0x00,
    SOLIDABLE = 0x01, /** 物体不可穿过 */
    DAMAGEABLE = 0x02,   /** 物体可以给与和接受伤害 */
    FORCEABLE = 0x04,    /** 物体在碰撞之后会根据自身速度和质量给另一个物体一个冲量 */
    INDESTRUCTIBLE = 0x08, /** 不可被摧毁的，这种物体在碰撞之后不会由于生命值为0而被销毁 */
    BULLETABLE = 0x10, /** 物体是子弹，子弹在每次碰撞之后都会将自己的生命值减1 */
    WAVEABLE = 0x20 /** 冲击波式，会伤害到范围内的所有Damageable单位 */
};

struct PhysicInfo{
    Vec a;
    Vec f;
    Vec v;
    float m;    /** 质量默认为1，如果为0不会受到力和冲量的影响，只能够改变速度 */
    PhysicInfo();
    void Update(float sec);
};

enum ColliLayer{
    LAYER_UNKNOWN = 0x00,
    BULLET = 0x01, //子弹层，子弹应该在的层
    ENEMY = 0x02, //敌人层，敌人所在的层
    PLAYER = 0x04, //玩家层，玩家所在的层
    BLOCK = 0x08 //块状物层，墙壁，门等固定无伤害物体的层
};

/**
 * @brief 用于碰撞检测的物理体
 */
class Object{
public:
    PhysicInfo physic_info;
    Object();
    explicit Object(AABB aabb);
    explicit Object(OBB obb);
    explicit Object(Circle circle);
    Object(const Object& obj);
    Object& operator=(const Object& obj);
    void SetLayer(ColliLayer layer);
    ColliLayer GetLayer() const;
    void AttachLayer(ColliLayer layer);
    void SetColliType();
    void Set(AABB aabb);
    void Set(OBB obb);
    void Set(Circle circle);
    bool Valid() const;
    int Refcount() const;
    Vec Center() const;
    void Move(float dx, float dy);
    void MoveTo(float x, float y);
    ColliType GetColliType() const;
    void SetColliType(ColliType type);
    void AttachColliType(ColliType type);
    void UnsetColliType(ColliType type);
    ObjType GetType() const;
    Circle* GetCircle();
    AABB* GetAABB();
    OBB* GetOBB();
    void Update(float sec);
    void AddImpulse(Vec impuls);    /** 给物体一个冲量 */
    ~Object();
private:
    Circle* circle;
    ColliLayer coll_layer;    /** 碰撞层，相同层的物体不会碰撞 */
    ColliType colli_type;   /** 碰撞的类别，不会自动设置，必须手动设置 */
    OBB* obb;
    AABB* aabb;
    int* refcount;
    ObjType type;
    void gainRefcount();
    void releaseRefcount();
    void release();
};

struct Manifold{
    Object* o1;
    Object* o2;
    float deepth;
    Vec dir;
    bool Valid() const;
    Manifold();
    Manifold(Object* obj1, Object* obj2);
};

bool PointInAABB(Vec p, AABB aabb);
bool AABBvsAABB(Manifold& m);
bool AABBvsCircle(Manifold& m);
bool AABBvsOBB(Manifold& m);
bool CirclevsAABB(Manifold& m);
bool OBBvsAABB(Manifold& m);
bool CirclevsCircle(Manifold& m);
bool OBBvsOBB(Manifold& m);
bool CirclevsOBB(Manifold& m);
bool OBBvsCircle(Manifold& m);

/**
 * @brief 通过obj1和obj2进行碰撞，并将碰撞的结果返回给m
 * @param obj1 第一个碰撞物体
 * @param obj2 第二个碰撞物体
 * @param m 返回的碰撞检测信息
 * @warn m参数的内容并不会对这个函数的结果受到影响。
 */
bool Collision(Object* obj1, Object* obj2, Manifold& m);

/**
 * @brief 处理碰撞检测的函数，如果你有自己的碰撞检测处理，可以加在这里
 * @param m 碰撞检测返回的信息
 * @param prop1 第一个物体(m.o1)的基本属性
 * @param prop2 第二个物体(m.o2)的基本属性
 *
 * 这个函数根据Object的碰撞分类(colli_type)来进行不同的碰撞之后的操作。
 */
void ColliDealFunc(Manifold& m, BasicProp* prop1, BasicProp* prop2);

#endif
