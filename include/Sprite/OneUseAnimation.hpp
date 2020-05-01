#ifndef ONEUSEANIMATION_HPP
#define ONEUSEANIMATION_HPP
#include "GameObject.hpp"
#include "Animation.hpp"
#include "WorldModel.hpp"
#include <vector>
using namespace std;

class OneUseAnimation : public GameObject{
public:
    static OneUseAnimation* Create();
    void Load(TextureSheet& ts, vector<int> delay);
    void Flip(FlipFlag fflag);
private:
    OneUseAnimation();
    void update() override;
    void draw() override;
    Animation ani;
    FlipFlag flipflag;
};

#endif
