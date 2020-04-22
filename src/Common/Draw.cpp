#include "Draw.hpp"

void SDL_DrawAABB(SDL_Renderer* render, AABB& aabb){
    SDL_Rect rect;
    rect.x = aabb.tl.x;
    rect.y = aabb.tl.y;
    rect.w = aabb.Width();
    rect.h = aabb.Height();
    SDL_RenderDrawRect(render, &rect);
}

void SDL_DrawOBB(SDL_Renderer* render, OBB& obb){
    Vec points[4];
    obb.GetPoints(points);
    for(int i=0;i<3;i++)
        SDL_RenderDrawLine(render, points[i].x, points[i].y, points[i+1].x, points[i+1].y);
    SDL_RenderDrawLine(render, points[0].x, points[0].y, points[3].x, points[3].y);
}

void SDL_DrawCircle(SDL_Renderer* render, Circle& c){
    float step = 10;
    float delta = 2*M_PI/step;
    for(int i=0;i<step;i++){
        SDL_RenderDrawLine(render, c.center.x+c.radius*cos(i*delta), c.center.y+c.radius*sin(i*delta), c.center.x+c.radius*cos((i+1)*delta), c.center.y+c.radius*sin((i+1)*delta));
    }
}
