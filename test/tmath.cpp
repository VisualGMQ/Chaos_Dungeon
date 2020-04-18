#include "math.hpp"

int main(){
    Vec2D v1(9, 2);
    Vec2D v2(3, 2);
    cout<<v1<<"+"<<v2<<"="<<v1+v2<<endl;
    cout<<v1<<"-"<<v2<<"="<<v1-v2<<endl;
    cout<<v1<<"*"<<v2<<"="<<v1*v2<<endl;
    cout<<v1<<"/"<<v2<<"="<<v1/v2<<endl;
    cout<<v1<<" dot "<<v2<<"="<<v1.Dot(v2)<<endl;
    cout<<v1<<" cross "<<v2<<"="<<v1.Cross(v2)<<endl;
    cout<<v1<<"*3="<<v1*3<<endl;
    Range r1(0, 10);
    Range r2(5, 20);
    cout<<"Combine "<<r1<<","<<r2<<CombineRange(r1, r2)<<endl;
    cout<<"Get cover of "<<r1<<","<<r2<<GetCoveredRange(r1, r2)<<endl;
    Mat22 m(1, 2, 3, 4);
    cout<<m<<"*"<<v1<<"="<<m*v1<<endl;
    return 0;
}
