#ifndef WALL_HPP
#define WALL_HPP
#include "Sprite.hpp"
#include "Collision.hpp"
#include "Colliable.hpp"
#include "ColliSystem.hpp"

class Wall : public ColliableSprite{
    DEFINE_DELETEINTERFACE(Wall)
    DEFINE_DELETEBODY(Wall)
public:
    void Init() override;
    int Width() const;
    int Height() const;
    void EventHandle(SDL_Event& event) override;
    ~Wall();
private:
    Wall() = default;
    Vec topleft() const;
    void update() override;
    void draw() override;
    Texture texture;
};

#endif
