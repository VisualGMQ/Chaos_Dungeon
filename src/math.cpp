#include "math.hpp"

Vec2D::Vec2D():x(0),y(0){}

Vec2D::Vec2D(float x, float y){
    this->x = x;
    this->y = y;
}

void Vec2D::Set(float nx, float ny){
    x = nx;
    y = ny;
}

float Vec2D::Cross(const Vec2D v) const{
    return x*v.y-y*v.x;
}

float Vec2D::Dot(const Vec2D v) const{
    return x*v.x+y*v.y;
}

void Vec2D::Normalize(){
    float len = Len();
    x /= len;
    y /= len;
}

float Vec2D::Len() const{
    return sqrt(x*x+y*y);
}

Vec2D Vec2D::operator=(const Vec2D v){
    x = v.x;
    y = v.y;
    return *this;
}

Vec2D Vec2D::operator+(const Vec2D v){
    return Vec2D(x+v.x, y+v.y);
}

Vec2D Vec2D::operator-(const Vec2D v){
    return Vec2D(x-v.x, y-v.y);
}

Vec2D Vec2D::operator*(const Vec2D v){
    return Vec2D(x*v.x, y*v.y);
}

Vec2D Vec2D::operator/(const Vec2D v){
    return Vec2D(x/v.x, y/v.y);
}

Vec2D Vec2D::operator+=(const Vec2D v){
    x += v.x;
    y += v.y;
    return *this;
}

Vec2D Vec2D::operator-=(const Vec2D v){
    x -= v.x;
    y -= v.y;
    return *this;
}

Vec2D Vec2D::operator*=(const Vec2D v){
    x *= v.x;
    y *= v.y;
    return *this;
}

Vec2D Vec2D::operator/=(const Vec2D v){
    x /= v.x;
    y /= v.y;
    return *this;
}

bool Vec2D::operator==(const Vec2D v){
    return FLT_CMP(x, v.x) && FLT_CMP(y, v.y);
}

bool Vec2D::operator!=(const Vec2D v){
    return !(*this==v);
}

ostream& operator<<(ostream& o, const Vec2D v){
    v.Print();
    return o;
}

Vec2D Vec2D::operator+(float v){
    return Vec2D(x+v, y+v);
}

Vec2D Vec2D::operator-(float v){
    return Vec2D(x-v, y-v);
}

Vec2D Vec2D::operator*(float v){
    return Vec2D(x*v, y*v);
}

Vec2D Vec2D::operator/(float v){
    return Vec2D(x/v, y/v);
}

Vec2D Vec2D::operator+=(float v){
    x += v;
    y += v;
    return *this;
}

Vec2D Vec2D::operator-=(float v){
    x -= v;
    y -= v;
    return *this;
}

Vec2D Vec2D::operator*=(float v){
    x *= v;
    y *= v;
    return *this;
}

Vec2D Vec2D::operator/=(float v){
    x /= v;
    y /= v;
    return *this;
}

Vec2D operator+(float n, Vec2D v){
    return v+n;
}

Vec2D operator-(float n, Vec2D v){
    return v-n;
}

Vec2D operator*(float n, Vec2D v){
    return v*n;
}

Vec2D operator/(float n, Vec2D v){
    return v/n;
}

float Distance(Vec2D v1, Vec2D v2){
    return sqrt(pow(v1.x-v2.x, 2)+pow(v1.y-v2.y, 2));
}

Vec2D Normalize(Vec2D v){
    float len = v.Len();
    if(len==0)
        return v;
    return Vec2D(v.x/len, v.y/len);
}

void Vec2D::Print() const{
    cout<<"("<<x<<","<<y<<")";
}

Range::Range():min(0),max(0){}

Range::Range(float a, float b){
    Set(a, b);
}

void Range::Set(float a, float b){
    this->min = a<b?a:b;
    this->max = a>b?a:b;
}

float Range::GetMax() const{
    return max;
}

float Range::GetMin() const{
    return min;
}

float Range::Len() const{
    return max-min;
}

void Range::Print() const{
    cout<<"Range("<<min<<" "<<max<<")";
}

ostream& operator<<(ostream& o, Range range){
    range.Print();
    return o;
}

Range GetCoveredRange(const Range r1, const Range r2){
    if(r1.GetMax()<=r2.GetMin() || r2.GetMax()<=r1.GetMin())
        return Range(0, 0);
    if(r1.GetMin()<=r2.GetMin() && r1.GetMax()<=r2.GetMax())
        return Range(r2.GetMin(), r1.GetMax());
    if(r1.GetMin()<=r2.GetMin() && r1.GetMax()>=r2.GetMax())
        return r2;
    if(r2.GetMin()<=r1.GetMin() && r2.GetMax()<=r1.GetMax())
        return Range(r1.GetMin(), r2.GetMax());
    if(r2.GetMin()<=r1.GetMin() && r2.GetMax()>=r1.GetMax())
        return r1;
}

Range CombineRange(const Range r1, const Range r2){
    return Range(std::min(r1.GetMin(), r2.GetMin()), std::max(r1.GetMax(), r2.GetMax()));
}

bool PointInRange(const Range r, float p){
    return r.GetMin()<=p && r.GetMax()>=p;
}

bool IsRangeCovered(const Range r1, const Range r2){
    return PointInRange(r2, r1.GetMin()) || PointInRange(r2, r1.GetMax()) || PointInRange(r1, r2.GetMin()) || PointInRange(r1, r2.GetMax());
}

Rot2D::Rot2D():c(1),s(0){}

Rot2D::Rot2D(float degree){
    Set(degree);
}

void Rot2D::Set(float degree){
    c = cos(DEG2RAD(degree));
    s = sin(DEG2RAD(degree));
}

Vec2D Rot2D::GetAxisX() const{
    return Vec2D(c, s);
}

Vec2D Rot2D::GetAxisY() const{
    return Vec2D(-s, c);
}

float Rot2D::GetDegree() const{
    return RAD2DEG(asin(s));
}

Mat22::Mat22(){
    Identify();
}

Mat22::Mat22(Vec2D c1, Vec2D c2){
    m00 = c1.x;
    m10 = c1.y;
    m01 = c2.x;
    m11 = c2.y;
}

Mat22::Mat22(float m00, float m01, float m10, float m11){
    this->m00 = m00;
    this->m01 = m01;
    this->m10 = m10;
    this->m11 = m11;
}

void Mat22::Identify(){
    m00 = m11 = 1;
    m01 = m10 = 0;
}

void Mat22::Zero(){
    m00 = m11 = m01 = m10 = 0;
}

Mat22 Mat22::operator+(const Mat22 m){
    return Mat22(m00+m.m00, m01+m.m01,
            m10+m.m10, m11+m.m11);
}

Mat22 Mat22::operator-(const Mat22 m){
    return Mat22(m00-m.m00, m01-m.m01,
            m10-m.m10, m11-m.m11);
}

Mat22 Mat22::operator*(const Mat22 m){
    return Mat22(m00*m.m00, m01*m.m01,
            m10*m.m10, m11*m.m11);
}

Mat22 Mat22::operator/(const Mat22 m){
    return Mat22(m00/m.m00, m01/m.m01,
            m10/m.m10, m11/m.m11);
}

Mat22 Mat22::operator+=(const Mat22 m){
    m00 += m.m00;
    m10 += m.m10;
    m11 += m.m11;
    m01 += m.m01;
    return *this;
}

Mat22 Mat22::operator-=(const Mat22 m){
    m00 -= m.m00;
    m10 -= m.m10;
    m11 -= m.m11;
    m01 -= m.m01;
    return *this;
}

Mat22 Mat22::operator*=(const Mat22 m){
    m00 *= m.m00;
    m10 *= m.m10;
    m11 *= m.m11;
    m01 *= m.m01;
    return *this;
}

Mat22 Mat22::operator/=(const Mat22 m){
    m00 /= m.m00;
    m10 /= m.m10;
    m11 /= m.m11;
    m01 /= m.m01;
    return *this;
}

Mat22 Mat22::operator*(float n){
    return Mat22(m00*n, m01*n, m10*n, m11*n);
}

Mat22 Mat22::operator/(float n){
    return Mat22(m00/n, m01/n, m10/n, m11/n);
}

Mat22 operator/(float n, Mat22 m){
    return m/n;
}

Mat22 Mat22::Times(const Mat22 m){
    return Mat22(m00*m.m00+m01*m.m10, m00*m.m01+m01*m.m11,
            m10*m.m00+m11*m.m10, m10*m.m01+m11*m.m11);
}

void Mat22::Print() const{
    cout<<"["<<m00<<" "<<m01<<","<<endl
        <<" "<<m10<<" "<<m11<<"]"<<endl;
}

ostream& operator<<(ostream& o, Mat22 m){
    m.Print();
    return o;
}

Vec2D Mat22::operator*(const Vec2D v){
    return Vec2D(m00*v.x+m01*v.y, m10*v.x+m11*v.y);
}

Mat22 GenRotMat22(float degree){
    float radian = RAD2DEG(degree);
    return Mat22(sin(radian), cos(radian), cos(radian), -sin(radian));
}
