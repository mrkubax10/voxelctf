#include "gui_progressbar.h"
GUIProgressbar::GUIProgressbar(int x,int y,int w,int h,TTF_Font *font,SDL_Renderer *render,int percents,int r,int g,int b,int r1,int g1,int b1){
    GUIProgressbar::x=x;
    GUIProgressbar::y=y;
    GUIProgressbar::w=w;
    GUIProgressbar::h=h;
    GUIProgressbar::font=font;
    GUIProgressbar::render=render;
    GUIProgressbar::percents=percents;
    GUIProgressbar::r=r;
    GUIProgressbar::g=g;
    GUIProgressbar::b=b;
    GUIProgressbar::r1=r1;
    GUIProgressbar::g1=g1;
    GUIProgressbar::b1=b1;
    GUIProgressbar::texturePercent=SDL_CreateTextureFromSurface(render,TTF_RenderText_Blended(font,std::to_string(percents).c_str(),{255,255,255}));
}
void GUIProgressbar::update(SDL_Event *ev){

}
void GUIProgressbar::draw(){
    guiRect.x=GUIProgressbar::x;
    guiRect.y=GUIProgressbar::y;
    guiRect.w=GUIProgressbar::w;
    guiRect.h=GUIProgressbar::h;
    SDL_SetRenderDrawColor(GUIProgressbar::render,GUIProgressbar::r,GUIProgressbar::g,GUIProgressbar::b,255);
    SDL_RenderFillRect(GUIProgressbar::render,&guiRect);
    guiRect.w=GUIProgressbar::percents<=100?GUIProgressbar::w*GUIProgressbar::percents/100:GUIProgressbar::w;
    SDL_SetRenderDrawColor(GUIProgressbar::render,GUIProgressbar::r1,GUIProgressbar::g1,GUIProgressbar::b1,255);
    SDL_RenderFillRect(GUIProgressbar::render,&guiRect);
    SDL_QueryTexture(GUIProgressbar::texturePercent,0,0,&guiRect.w,&guiRect.h);
    guiRect.x=GUIProgressbar::x+GUIProgressbar::w+4;
    guiRect.y=GUIProgressbar::y+(GUIProgressbar::h-guiRect.h)/2;
    SDL_RenderCopy(GUIProgressbar::render,GUIProgressbar::texturePercent,0,&guiRect);
}
void GUIProgressbar::setPercentage(int percents){
    GUIProgressbar::percents=percents;
    SDL_DestroyTexture(GUIProgressbar::texturePercent);
    GUIProgressbar::texturePercent=SDL_CreateTextureFromSurface(GUIProgressbar::render,TTF_RenderText_Blended(GUIProgressbar::font,std::to_string(GUIProgressbar::percents).c_str(),{255,255,255}));
}
int GUIProgressbar::getPercentage(){
    return GUIProgressbar::percents;
}
void GUIProgressbar::addPercents(int percents){
    GUIProgressbar::setPercentage(GUIProgressbar::getPercentage()+percents);
}
