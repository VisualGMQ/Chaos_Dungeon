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

Object::Object():circle(nullptr),obb(nullptr),aabb(nullptr),type(ObjType::OBJ_TYPE_UNKNOWN),coll_layer(ColliLayer::LAYER_UNKNOWN),colli_type(ColliType::COLLI_TYPE_UNKNOWN){
    refcount = new int(0);
    gainRefcount();
}

Object::Object(const Object& obj){
    refcount = nullptr;
    *this = obj;
}

Object& Object::operator=(const Object& obj){
    if(refcount)
        releaseRefcount();
    circle = obj.circle;
    obb = obj.obb;
    aabb = obj.aabb;
    type = obj.type;
    refcount = obj.refcount;
    colli_type = obj.colli_type;
    coll_layer = obj.coll_layer;
    physic_info = obj.physic_info;
    gainRefcount();
    return *this;
}

void Object::SetLayer(ColliLayer layer){
    SET_STATE(coll_layer, layer);
}

void Object::AttachLayer(ColliLayer layer){
    ATTACH_STATE(this->coll_layer, layer, ColliLayer);
}

void Object::UnsetColliType(ColliType type){
    UNSET_STATE(colli_type, type, ColliType);
}

ColliType Object::GetColliType() const{
    return colli_type;
}

void Object::SetColliType(ColliType type){
    colli_type = type;
}

void Object::AttachColliType(ColliType type){
    colli_type = static_cast<ColliType>(colli_type|type);
}

ColliLayer Object::GetLayer() const{
    return coll_layer;
}

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
    this->aabb = new AABB(aabb);
}

void Object::Set(OBB obb){
    type = ObjType::OBB;
    this->obb = new OBB(obb);
}

void Object::Set(Circle circle){
    type = ObjType::CIRCLE;
    this->circle = new Circle(circle);
}

void Object::gainRefcount(){
    if(refcount)
        (*refcount)++;
}

bool Object::Valid() const{
    return circle || obb || aabb;
}

void Object::releaseRefcount(){
    (*refcount)--;
    if((*refcount)==0)
        release();
}

void Object::release(){
    if(obb)
        delete obb;
    if(aabb)
        delete aabb;
    if(circle)
        delete circle;
    if(refcount)
        delete refcount;
}

Vec Object::Center() const{
    if(type==ObjType::AABB)
        return aabb->Center();
    if(type==ObjType::CIRCLE)
        return circle->center;
    if(type==ObjType::OBB)
        return obb->center;
    return Vec();
}

void Object::Move(float dx, float dy){
    if(type==ObjType::AABB)
        aabb->Move(dx, dy);
    if(type==ObjType::CIRCLE)
        circle->center += Vec(dx, dy);
    if(type==ObjType::OBB)
        obb->center += Vec(dx, dy);
}

void Object::MoveTo(float x, float y){
    if(type==ObjType::AABB)
        aabb->MoveTo(x, y);
    if(type==ObjType::CIRCLE)
        circle->center.Set(x, y);
    if(type==ObjType::OBB)
        obb->center.Set(x, y);
}

ObjType Object::GetType() const{
    return type;
}

Circle* Object::GetCircle(){
    if(circle==nullptr)
        cerr<<"object's circle is null, please check it's type"<<endl;
    return circle;
}

AABB* Object::GetAABB(){
    if(aabb==nullptr)
        cerr<<"object's aabb is null, please check it's type"<<endl;
    return aabb;
}

OBB* Object::GetOBB(){
    if(obb==nullptr)
        cerr<<"object's obb is null, please check it's type"<<endl;
    return obb;
}

int Object::Refcount() const{
    if(refcount)
    return *refcount;
}

PhysicInfo::PhysicInfo():m(1){}

void PhysicInfo::Update(float sec){
    if(m!=0){
        a = f/m;
        v += a*sec;
        f.Set(0, 0);
    }
}

void Object::Update(float sec){
    physic_info.Update(sec);
    Move(physic_info.v.x, physic_info.v.y);
}

void Object::AddImpulse(Vec impuls){
    if(physic_info.m!=0)
        physic_info.v += impuls/physic_info.m;
}

Object::~Object(){
    releaseRefcount();
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
    bool ret = AABBvsCircle(newm);
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

bool obbcollicircle(Vec axis, Manifold& m){
    Circle* c = m.o1->GetCircle();
    OBB* obb = m.o2->GetOBB();

}

bool CirclevsOBB(Manifold& m){
#warning "CirclevsOBB is not finish"

}

bool OBBvsCircle(Manifold& m){
#warning "OBBvsCircle is not finish"
}

/**
 * @brief 碰撞检测的函数指针，内部使用
 */
using colliCallBack = bool(*)(Manifold& m);

/**
 * @brief 碰撞表
 */
static colliCallBack collitable[4][4] = {
    /* UNKNOWN vs Other */
    {nullptr, nullptr, nullptr, nullptr},
    /* Circle vs Other */
    {nullptr, CirclevsCircle, CirclevsAABB, CirclevsOBB},
    /* AABB vs Other */
    {nullptr, AABBvsCircle, AABBvsAABB, AABBvsOBB},
    /* OBB vs Other */
    {nullptr, OBBvsCircle, OBBvsAABB, OBBvsOBB}
};

bool Collision(Object* obj1, Object* obj2, Manifold& m){
    //具有相同层的物体不应当碰撞
    if(obj1->GetLayer()&obj2->GetLayer())
        return false;
    int type1 = static_cast<int>(obj1->GetType()),
        type2 = static_cast<int>(obj2->GetType());
    bool ret = false;
    int retrive_count = 0;
    m.o1 = obj1;
    m.o2 = obj2;
    if(!collitable[type1][type2])
        return false;
    do{
        ret = ret || collitable[type1][type2](m);
        retrive_count++;
    }while(ret && retrive_count<RETRIVE_COLLI_NUM);
    return ret;
}

void ColliDealFunc(Manifold& m, BasicProp* prop1, BasicProp* prop2){
    Vec v_o1o2 = m.o2->Center()-m.o1->Center();
    //如果双方都是SOLIDABLE，那么应当碰撞后分离
    if(HAS_STATE(m.o1->GetColliType(), ColliType::SOLIDABLE)&&HAS_STATE(m.o2->GetColliType(), ColliType::SOLIDABLE)){
        char sign = v_o1o2.Dot(m.dir)>=0?-1:1;
        if(m.o1->physic_info.m!=0)
            m.o1->Move(sign*m.deepth*m.dir.x, sign*m.deepth*m.dir.y);
        if(m.o2->physic_info.m!=0)
            m.o2->Move(-sign*m.deepth*m.dir.x, -sign*m.deepth*m.dir.y);
    }

    //DAMAGEABLE在碰撞之后生命值会减去对方的伤害值
    if(prop1 && prop2 && prop2->can_damage && HAS_STATE(m.o1->GetColliType(), ColliType::DAMAGEABLE)){
        prop1->hp -= prop2->damage;
        prop2->can_damage = false;
    }
    if(prop2 && prop2 && prop1->can_damage && HAS_STATE(m.o2->GetColliType(), ColliType::DAMAGEABLE)){
        prop2->hp -= prop1->damage;
        prop1->can_damage = false;
    }

    //BULLETABLE在碰撞之后会将自己的生命值减1
    if(prop1 && HAS_STATE(m.o1->GetColliType(), ColliType::BULLETABLE)){
        prop1->hp--;
    }
    if(prop2 && HAS_STATE(m.o2->GetColliType(), ColliType::BULLETABLE)){
        prop2->hp--;
    }
}
