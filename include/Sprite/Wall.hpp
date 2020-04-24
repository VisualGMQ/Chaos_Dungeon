#ifndef WALL_HPP
#define WALL_HPP
#include "Sprite.hpp"
#include "Collision.hpp"
#include "Colliable.hpp"

class Wall : public ColliableSprite{
public:
    Wall() = default;
    void Init() override;
    int Width() const;
    int Height() const;
    void EventHandle(SDL_Event& event) override;
private:
    Vec topleft() const;
    void update() override;
    void draw() override;
    Texture texture;
};

#endif
