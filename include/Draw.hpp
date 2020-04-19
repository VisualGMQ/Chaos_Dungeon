#ifndef DRAW_HPP
#define DRAW_HPP
#include "Collision.hpp"
#include "SDL.h"
#include "Texture.hpp"
#include "Animation.hpp"

void SDL_DrawAABB(SDL_Renderer* render, AABB& aabb);
void SDL_DrawOBB(SDL_Renderer* render, OBB& obb);
void SDL_DrawCircle(SDL_Renderer* render, Circle& c);
/**
 * @brief 绘制额Texture
 * @param w 如果为0的话表示绘制原来的宽度
 * @param h 如果为0的话表示绘制原来的高度
 */
void SDL_DrawTexture(Texture& t, int x, int y, int w=0, int h=0);
void SDL_DrawTextureFromSheet(TextureSheet& ts, int c, int r, int x, int y, int w=0, int h=0);
void SDL_DrawAnimation(Animation& ani, int x, int y, int w=0, int h=0);
void SDL_DrawAnimationS(AnimationS& ani, int x, int y, int w=0, int h=0);

#endif
