#ifndef MATH_HPP
#define MATH_HPP
#include <cfloat>
#include <cmath>
#include <iostream>
#include <vector>
#include "glm/glm.hpp"
using namespace std;
#define FLT_CMP(a, b) (abs(a-b)<=FLT_EPSILON)
#define DEG2RAD(x) (x*M_PI/180.0)
#define RAD2DEG(x) (x*180.0/M_PI)

template <typename T>
ostream& operator<<(ostream& o, const vector<T>& v){
    cout<<"[";
    for(int i=0;i<v.size();i++)
        cout<<v[i]<<" ";
    cout<<"]";
    return o;
}

struct Size{
    float w;
    float h;
    Size();
};

class Vec2D{
public:
    Vec2D();
    Vec2D(float x, float y);
    void Set(float x, float y);
    void Normalize();
    float Len() const;
    float Cross(const Vec2D v) const;
    float Dot(const Vec2D v) const;
    Vec2D operator=(const Vec2D v);
    Vec2D operator+(const Vec2D v);
    Vec2D operator-(const Vec2D v);
    Vec2D operator*(const Vec2D v);
    Vec2D operator/(const Vec2D v);
    Vec2D operator+=(const Vec2D v);
    Vec2D operator-=(const Vec2D v);
    Vec2D operator*=(const Vec2D v);
    Vec2D operator/=(const Vec2D v);
    bool operator==(const Vec2D v);
    bool operator!=(const Vec2D v);
    Vec2D operator+(float v);
    Vec2D operator-(float v);
    Vec2D operator*(float v);
    Vec2D operator/(float v);
    Vec2D operator+=(float v);
    Vec2D operator-=(float v);
    Vec2D operator*=(float v);
    Vec2D operator/=(float v);
    float x;
    float y;
    void Print() const;
};

float Distance(Vec2D v1, Vec2D v2);
Vec2D Normalize(Vec2D v);

Vec2D operator+(float n, Vec2D v);
Vec2D operator-(float n, Vec2D v);
Vec2D operator*(float n, Vec2D v);
Vec2D operator/(float n, Vec2D v);
ostream& operator<<(ostream& o, const Vec2D v);

using Vec = Vec2D;

struct Range{
    Range();
    Range(float a, float b);
    void Set(float a, float b);
    float GetMax() const;
    float GetMin() const;
    float Len() const;
    float min;
    float max;
    void Print() const;
};

ostream& operator<<(ostream& o, Range range);

Range GetCoveredRange(const Range r1, const Range r2);
Range CombineRange(const Range r1, const Range r2);
bool PointInRange(const Range r, float p);
bool IsRangeCovered(const Range r1, const Range r2);

class Rot2D{
public:
    Rot2D();
    Rot2D(float degree);
    void Set(float degree);
    Vec2D GetAxisX() const;
    Vec2D GetAxisY() const;
    float GetDegree() const;
private:
    float s;
    float c;
};

struct Mat22{
    Mat22();
    Mat22(Vec2D c1, Vec2D c2);
    Mat22(float m00, float m01, float m10, float m11);
    void Identify();
    void Zero();
    Mat22 Times(const Mat22 m);
    Mat22 operator+(const Mat22 m);
    Mat22 operator-(const Mat22 m);
    Mat22 operator*(const Mat22 m);
    Vec2D operator*(const Vec2D v);
    Mat22 operator*(float n);
    Mat22 operator/(const Mat22 m);
    Mat22 operator/(float n);
    Mat22 operator+=(const Mat22 m);
    Mat22 operator-=(const Mat22 m);
    Mat22 operator*=(const Mat22 m);
    Mat22 operator/=(const Mat22 m);
    float m00;
    float m01;
    float m10;
    float m11;
    void Print() const;
};

ostream& operator<<(ostream& o, Mat22 m);

Mat22 operator*(float n, Mat22 m);
Mat22 operator/(float n, Mat22 m);

Mat22 GenRotMat22(float degree);

#endif
