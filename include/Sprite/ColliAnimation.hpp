#ifndef COLLIANIMATION_HPP
#define COLLIANIMATION_HPP
#include "Animation.hpp"
#include "BasicProp.hpp"
#include "Drawable.hpp"
using namespace std;

struct ColliRange{
    int lower;  /** 碰撞开始的帧 */
    int upper;  /** 碰撞结束的帧 */
    int damage; /** 碰撞时产生的伤害 */
    ColliRange();
    bool Valid() const;
};

class ColliAnimation : public Animation{
public:
    ColliAnimation();
    ColliAnimation(vector<Frame> frame_list);
    ColliAnimation(initializer_list<Frame> frame_list);
    ColliAnimation(TextureSheet& sheet, vector<int> delay, int begin = 0, int end = -1);
    void Pause() override;
    void Stop() override;
    void SetColliRange(int lower, int upper, int damage);
    bool Valid() const override;
    void BindProp(BasicProp* p);
    void Update() override;
private:
    BasicProp* prop; 
    ColliRange range;
    bool changed_to_colli;
};

#endif
