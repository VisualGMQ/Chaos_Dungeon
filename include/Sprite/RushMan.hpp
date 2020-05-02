#ifndef RUSHMAN_HPP
#define RUSHMAN_HPP
#include "Texture.hpp"
#include "Animation.hpp"
#include "Creature.hpp"
#include "Drawable.hpp"

class RunMan : public Creature{
public:
    static RunMan* Create();
    void Init() override;
private:
    RunMan();
    void update() override;
    void draw() override;
    void alive_logic() override;
    void die_logic() override;
    Animation ani_walk;
    Texture tex_stand;
    Animation ani_rush;
    Texture tex_die;
    Animation ani_throw;
};

#endif
