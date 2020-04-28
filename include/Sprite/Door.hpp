#ifndef DOOR_HPP
#define DOOR_HPP
#include "Sprite.hpp"
#include "Animation.hpp"
#include "Drawable.hpp"
#include "ColliSystem.hpp"

class Door : public ColliableSprite{
public:
    enum State{
        OPEN,
        CLOSE
    };
    static Door* Create();
    void Init() override;
    void Open();
    void Close();
    int Width() const;
    int Height() const;
    ~Door();
private:
    void update() override;
    void draw() override;
    Door();
    Animation ani_close;
    Animation ani_open;
    Texture tex_close;
    Texture tex_open;
    Drawable* draw_ptr;
    State state;
};

#endif
