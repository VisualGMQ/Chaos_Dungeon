#ifndef KILLEDENEMYNUM_HPP
#define KILLEDENEMYNUM_HPP
#include "Number.hpp"
#include "GameObject.hpp"
/**
 * @brief 单例类，用于存储杀掉的敌人个数
 */
class KilledEnemyNum_Sington : public GameObject{
public:
    static KilledEnemyNum_Sington* GetInstance();
    void IncreaseOneNum();
    int GetNum() const;
    void Scale(float sx, float sy);
private:
    void update() override;
    void draw() override;
    KilledEnemyNum_Sington();
    static KilledEnemyNum_Sington* instance;
    Number* num;
    int enemy_num;
    Texture tex;
};

#endif
