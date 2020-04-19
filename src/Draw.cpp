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

void SDL_DrawTexture(Texture& t, int x, int y, int w, int h){
    SDL_Rect rect = {x, y, w, h};
    if(w==0)
        rect.w = t.Width();
    if(h==0)
        rect.h = t.Height();
    SDL_RenderCopy(Director::GetInstance()->GetRender(), t.GetTexture(), nullptr, &rect);
}

void SDL_DrawTextureFromSheet(TextureSheet& ts, int c, int r, int x, int y, int w, int h){
    SDL_Rect rect = ts.Get(c, r);
    SDL_Rect dst_rect = {x, y, w, h};
    if(w==0)
        dst_rect.w = ts.Width();
    if(h==0)
        dst_rect.h = ts.Height();
    SDL_RenderCopy(Director::GetInstance()->GetRender(), ts.GetTexture().GetTexture(), &rect, &dst_rect);
}

void SDL_DrawAnimation(Animation& ani, int x, int y, int w, int h){
    SDL_DrawTexture(ani.GetCurrentTexture(), x, y, w, h);
}

void SDL_DrawAnimationS(AnimationS& ani, int x, int y, int w, int h){
    SDL_Rect src_rect = ani.GetCurrentRect();
    SDL_Rect dst_rect = {x, y, w, h};
    if(w==0)
        dst_rect.w = ani.GetSheet().Width();
    if(h==0)
        dst_rect.h = ani.GetSheet().Height();
    SDL_RenderCopy(Director::GetInstance()->GetRender(), ani.GetSheet().GetTexture().GetTexture(), &src_rect, &dst_rect);
}
