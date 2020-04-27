#ifndef WALL_HPP
#define WALL_HPP
#include "Sprite.hpp"
#include "Collision.hpp"
#include "Colliable.hpp"
#include "ColliSystem.hpp"
#include "Texture.hpp"

class Wall : public ColliableSprite{
public:
    static Wall* Create();
    void Init() override;
    int Width() const;
    int Height() const;
    ~Wall();
private:
    Wall();
    Vec topleft() const;
    void update() override;
    void draw() override;
    Texture texture;
};

#endif
