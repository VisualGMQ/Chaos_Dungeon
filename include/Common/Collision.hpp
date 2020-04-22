#ifndef COLLISION_HPP
#define COLLISION_HPP
#include "math.hpp"

struct AABB{
    AABB() = default;
    AABB(float x, float y, float w, float h);
    AABB(Vec tl, Vec br);
    Vec Center() const;
    void MoveTo(float x, float y);
    void Move(float dx, float dy);
    float Width() const;
    float Height() const;
    Vec tl;
    Vec br;
};

struct OBB{
    OBB() = default;
    OBB(Vec cent, float w_2, float h_2, float degree);
    void GetPoints(Vec points[4]);
    Vec center;
    Rot2D rotation;
    float half_w;
    float half_h;
};

struct Circle{
    Circle();
    Circle(float cx, float cy, float r);
    Vec center;
    float radius;
};

enum class ObjType{
    CIRCLE,
    AABB,
    OBB,
    UNKNOWN
};

class Object{
public:
    Object();
    explicit Object(AABB aabb);
    explicit Object(OBB obb);
    explicit Object(Circle circle);
    void Set(AABB aabb);
    void Set(OBB obb);
    void Set(Circle circle);
    Vec Center() const;
    ObjType GetType() const;
    Circle* GetCircle();
    AABB* GetAABB();
    OBB* GetOBB();
    ~Object();
private:
    Circle* circle;
    OBB* obb;
    AABB* aabb;
    ObjType type;
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

#endif
