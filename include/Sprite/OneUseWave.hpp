#ifndef ONEUSEWAVE_HPP
#define ONEUSEWAVE_HPP
#include "DamageableSprite.hpp"

/**
 * @brief 一次性冲击波，放入ColliSystem的话会立刻和其他物理体产生反应并且在下一帧被销毁
 */
class OneUseWave : public DamageableSprite{
public:
    static OneUseWave* Create();
    void Init() override;
    bool IsValid() const;
    void InValid();
    void SetWaveColliCircle(Circle c);
    void SetWaveColliRect(AABB rect);
private:
    void update() override;
    void draw() override;
    OneUseWave();
    bool isvalid;
};

#endif
