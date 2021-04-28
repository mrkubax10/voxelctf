#include "gui_slider.h"
GUISlider::GUISlider(int x,int y,int w,int h,TTF_Font *font,SDL_Renderer *render,float value){
    GUISlider::x=x;
    GUISlider::y=y;
    GUISlider::w=w;
    GUISlider::h=h;
    GUISlider::value=value;
    GUISlider::font=font;
    GUISlider::render=render;
    GUISlider::textureValue=SDL_CreateTextureFromSurface(render,TTF_RenderText_Blended(font,std::to_string((int)std::floor(value*100)).c_str(),{255,255,255}));
}
void GUISlider::update(SDL_Event *ev){

}
void GUISlider::draw(){
    guiRect.x=GUISlider::x;
    guiRect.y=GUISlider::y;
    guiRect.w=GUISlider::w;
    guiRect.h=GUISlider::h;
    SDL_SetRenderDrawColor(GUISlider::render,100,100,100,255);
    SDL_RenderFillRect(GUISlider::render,&guiRect);
    guiRect.x=GUISlider::x+(GUISlider::value*GUISlider::w);
    guiRect.y=GUISlider::y-2;
    guiRect.w=10;
    guiRect.h=GUISlider::h+4;
    SDL_SetRenderDrawColor(GUISlider::render,0,0,100,255);
    SDL_RenderFillRect(GUISlider::render,&guiRect);
    SDL_QueryTexture(GUISlider::textureValue,0,0,&guiRect.w,&guiRect.h);
    guiRect.x=GUISlider::x+GUISlider::w+8;
    guiRect.y=GUISlider::y+(GUISlider::h-guiRect.h);
    SDL_RenderCopy(GUISlider::render,GUISlider::textureValue,0,&guiRect);
    SDL_GetMouseState(&guiRect.x,&guiRect.y);
    if(SDL_GetMouseState(0,0)==SDL_BUTTON_LEFT && guiRect.x>=GUISlider::x && guiRect.x<=GUISlider::x+GUISlider::w && guiRect.y>=GUISlider::y && guiRect.y<=GUISlider::y+GUISlider::h){
        GUISlider::setValue((float)(guiRect.x-GUISlider::x)/GUISlider::w);
    }
}
void GUISlider::setValue(float value){
    GUISlider::value=value;
    SDL_DestroyTexture(GUISlider::textureValue);
    GUISlider::textureValue=SDL_CreateTextureFromSurface(GUISlider::render,TTF_RenderText_Blended(GUISlider::font,std::to_string((int)std::floor(GUISlider::value*100)).c_str(),{255,255,255}));
}
void GUISlider::addValue(float value){
    GUISlider::setValue(GUISlider::getValue()+value);
}
float GUISlider::getValue(){
    return GUISlider::value;
}
