#ifndef DRAW_HPP
#define DRAW_HPP
#include "Collision.hpp"
#include "SDL.h"

void SDL_DrawAABB(SDL_Renderer* render, AABB& aabb);
void SDL_DrawOBB(SDL_Renderer* render, OBB& obb);
void SDL_DrawCircle(SDL_Renderer* render, Circle& c);

#endif
