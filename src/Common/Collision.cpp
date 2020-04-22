#include "Collision.hpp"

AABB::AABB(float x, float y, float w, float h){
    tl.x = x;
    tl.y = y;
    br.x = tl.x+w;
    br.y = tl.x+h;
}

AABB::AABB(Vec tl, Vec br){
    this->tl = tl;
    this->br = br;
}

void AABB::MoveTo(float x, float y){
    float w = Width(), h = Height();
    tl.x = x;
    tl.y = y;
    br.x = tl.x+w;
    br.y = tl.y+h;
}

void AABB::Move(float dx, float dy){
    tl.x += dx;
    tl.y += dy;
    br.x += dx;
    br.y += dy;
}

float AABB::Width() const{
    return br.x-tl.x;
}

float AABB::Height() const{
    return br.y-tl.y;
}

Vec AABB::Center() const {
    return Vec((tl.x+br.x)/2, (tl.y+br.y)/2);
}

OBB::OBB(Vec cent, float w_2, float h_2, float degree):center(cent),half_h(h_2),half_w(w_2),rotation(degree){}

void OBB::GetPoints(Vec points[4]){
    Vec axis_x = rotation.GetAxisX()*half_w,
        axis_y = rotation.GetAxisY()*half_h;
    points[0] = center+axis_x+axis_y;
    points[1] = center+axis_x-axis_y;
    points[2] = center-axis_x-axis_y;
    points[3] = center-axis_x+axis_y;
}

Circle::Circle(float cx, float cy, float r):center(cx, cy),radius(r){}

Circle::Circle():radius(0){}

Manifold::Manifold():o1(nullptr),o2(nullptr),deepth(0){}

Manifold::Manifold(Object* obj1, Object* obj2):o1(obj1),o2(obj2),deepth(0){}

bool Manifold::Valid() const{
    return o1 && o2;
}

Object::Object():circle(nullptr),obb(nullptr),aabb(nullptr),type(ObjType::UNKNOWN){}

Object::Object(AABB aabb):Object(){
    Set(aabb);
}

Object::Object(OBB obb):Object(){
    Set(obb);
}

Object::Object(Circle circle):Object(){
    Set(circle);
}

void Object::Set(AABB aabb){
    type = ObjType::AABB;
    this->aabb = new AABB;
    *(this->aabb) = aabb;
}

void Object::Set(OBB obb){
    type = ObjType::OBB;
    this->obb = new OBB;
    *(this->obb) = obb;
}

void Object::Set(Circle circle){
    type = ObjType::CIRCLE;
    this->circle = new Circle;
    *(this->circle) = circle;
}

Vec Object::Center() const{
    if(type==ObjType::AABB)
        return aabb->Center();
    if(type==ObjType::CIRCLE)
        return circle->center;
    if(type==ObjType::OBB)
        return obb->center;
}

ObjType Object::GetType() const{
    return type;
}

Circle* Object::GetCircle(){
    return circle;
}

AABB* Object::GetAABB(){
    return aabb;
}

OBB* Object::GetOBB(){
    return obb;
}

Object::~Object(){
    if(obb)
        delete obb;
    if(aabb)
        delete aabb;
    if(circle)
        delete circle;
}

bool AABBvsAABB(Manifold& m){
    AABB* aabb1 = m.o1->GetAABB(), 
         *aabb2 = m.o2->GetAABB();
    Range vert1(aabb1->tl.y, aabb1->br.y),
          vert2(aabb2->tl.y, aabb2->br.y),
          hori1(aabb1->tl.x, aabb1->br.x),
          hori2(aabb2->tl.x, aabb2->br.x);
    float vert_len = GetCoveredRange(vert1, vert2).Len(),
          hori_len = GetCoveredRange(hori1, hori2).Len();
    if(vert_len==0 || hori_len==0)
        return false;
    if(vert_len<=hori_len){
        m.dir.Set(0, 1);
        m.deepth =  vert_len;
        return true;
    }else{
        m.dir.Set(1, 0);
        m.deepth =  hori_len;
        return true;
    }
}

bool AABBvsCircle(Manifold& m){
    AABB* aabb = m.o1->GetAABB();
    Circle* circle = m.o2->GetCircle();
    Vec near_point;
    Vec c_center = circle->center;
    if(c_center.x<=aabb->tl.x){
        near_point.x = aabb->tl.x;
        if(c_center.y<=aabb->tl.y)
            near_point.y = aabb->tl.y;
        else if(c_center.y>=aabb->br.y)
            near_point.y = aabb->br.y;
        else
            near_point.y = c_center.y;
    }else if(c_center.x>=aabb->br.x){
        near_point.x = aabb->br.x;
        if(c_center.y<=aabb->tl.y)
            near_point.y = aabb->tl.y;
        else if(c_center.y>=aabb->br.y)
            near_point.y = aabb->br.y;
        else
            near_point.y = c_center.y;
    }else{
        near_point.x = c_center.x;
        if(abs(c_center.y-aabb->tl.y)<abs(c_center.y-aabb->br.y))
            near_point.y = aabb->tl.y;
        else
            near_point.y = aabb->br.y;
    }
    if(PointInAABB(c_center, *aabb)){
        m.deepth = circle->radius+Distance(c_center, near_point);
        m.dir = Normalize(near_point-c_center);
        return true;
    }else{
        float dist = Distance(c_center, near_point);
        if(dist>=circle->radius)
            return false;
        else{
            m.deepth = circle->radius-dist;
            m.dir = Normalize(near_point-c_center);
            return true;
        }
    }
}

bool PointInAABB(Vec p, AABB aabb){
    return p.x>aabb.tl.x&&p.x<aabb.br.x&&p.y>aabb.tl.y&&p.y<aabb.br.y;
}

bool CirclevsCircle(Manifold& m){
    Circle* c1 = m.o1->GetCircle(),
           *c2 = m.o2->GetCircle();
    float distance2 = (c1->center.x-c2->center.x)*(c1->center.x-c2->center.x)+(c1->center.y-c2->center.y)*(c1->center.y-c2->center.y);
    cout<<"distance2"<<distance2<<endl;
    if(distance2>=pow(c1->radius+c2->radius, 2))
        return false;
    m.dir = Normalize(c1->center-c2->center);
    m.deepth = c1->radius+c2->radius-sqrt(distance2);
    return true;
}

/**
 * @brief 得到points在axis上的最长投影区间
 * @warn 这里默认axis参数是单位向量
 */
Range getOBBRangeOnAxis(Vec axis, Vec points[4]){
    float value[4];
    for(int i=0;i<4;i++)
        value[i] = axis.Dot(points[i]);
    pair<float, float> mm = minmax({value[0], value[1], value[2], value[3]});
    return Range(mm.first, mm.second);
}

float getOBBCoverOnAxis(Vec axis, Vec points1[4], Vec points2[4]){
    Range r1 = getOBBRangeOnAxis(axis, points1),
          r2 = getOBBRangeOnAxis(axis, points2);
    return GetCoveredRange(r1, r2).Len();
}

bool manifoldAssign(Manifold& m, Vec axis, Vec points1[4], Vec points2[4]){
    float cover=getOBBCoverOnAxis(axis, points1, points2);
    if(cover==0)
        return false;
    if(cover<m.deepth){
        m.deepth = cover;
        m.dir = axis;
    }
    return true;
}

bool OBBvsOBB(Manifold& m){
    OBB* obb1 = m.o1->GetOBB(),
        *obb2 = m.o2->GetOBB();
    Vec points1[4], points2[4];
    obb1->GetPoints(points1);
    obb2->GetPoints(points2);
    Vec axis_x1 = obb1->rotation.GetAxisX(),
        axis_y1 = obb1->rotation.GetAxisY(),
        axis_x2 = obb2->rotation.GetAxisX(),
        axis_y2 = obb2->rotation.GetAxisY();
    m.deepth = FLT_MAX;
    if(manifoldAssign(m, axis_x1, points1, points2) &&
        manifoldAssign(m, axis_y1, points1, points2) &&
        manifoldAssign(m, axis_x2, points1, points2) &&
        manifoldAssign(m, axis_y2, points1, points2))
        return true;
    return false;
}

bool CirclevsAABB(Manifold& m){
    Manifold newm;
    newm.o1 = m.o2;
    newm.o2 = m.o1;
    bool ret = AABBvsCircle(m);
    if(!ret)
        return false;
    m.deepth = newm.deepth;
    m.dir = newm.dir;
    return true;
}

float getAABBOBBCoveredLen(Vec axis, Range& aabb_range, Vec points[4]){
    return GetCoveredRange(aabb_range, getOBBRangeOnAxis(axis, points)).Len();
}

bool manifoldAssignAABBOBB(Manifold& m, Vec axis, Range r, Vec points[4]){
    float cover_len = getAABBOBBCoveredLen(axis, r, points);
    if(cover_len==0)
        return false;
    if(cover_len<m.deepth){
        m.deepth = cover_len;
        m.dir = axis;
    }
    return true;
}

bool AABBvsOBB(Manifold& m){
    AABB* aabb = m.o1->GetAABB();
    OBB* obb = m.o2->GetOBB();
    OBB obb2;
    obb2.center = aabb->Center();
    obb2.half_w = (aabb->tl.x-aabb->br.x)/2;
    obb2.half_h = (aabb->tl.y-aabb->br.y)/2;
    obb2.rotation.Set(0);
    Manifold m2;
    Object newo(obb2);
    m2.o1 = &newo;
    m2.o2 = m.o2;
    bool ret = OBBvsOBB(m2);
    if(!ret)
        return false;
    m.deepth = m2.deepth;
    m.dir = m2.dir;
    return true;
}

bool OBBvsAABB(Manifold& m){
    Manifold newm;
    newm.o1 = m.o2;
    newm.o2 = m.o1;
    bool ret = AABBvsOBB(newm);
    if(!ret)
        return false;
    m.deepth = newm.deepth;
    m.dir = newm.dir;
    return true;
}
