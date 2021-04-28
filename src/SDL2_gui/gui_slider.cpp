#include "gui_slider.h"
#include "../framework/app.hpp"
GUISlider::GUISlider(int x,int y,int w,int h,Renderer* renderer,TTF_Font *font,float value){
    GUISlider::x=x;
    GUISlider::y=y;
    GUISlider::w=w;
    GUISlider::h=h;
    GUISlider::value=value;
    GUISlider::font=font;
    GUISlider::renderer=renderer;
    GUISlider::textureValue=new Texture();
    SDL_Surface* surf=TTF_RenderText_Blended(font,std::to_string((int)std::floor(value*100)).c_str(),{255,255,255});
    textureValue->loadFromSurface(surf);
    SDL_FreeSurface(surf);
}
void GUISlider::update(SDL_Event *ev){

}
void GUISlider::draw(){
    renderer->drawColoredRect(glm::vec4(100.0f/255.0f,100.0f/255.0f,100.0f/255.0f,1),glm::vec2(x,y),glm::vec2(w,h));
    renderer->drawColoredRect(glm::vec4(0,0,100.0f/255.0f,1),glm::vec2(GUISlider::x+(GUISlider::value*GUISlider::w),GUISlider::y-2),glm::vec2(10,GUISlider::h+4));
    renderer->drawTexturedRect(textureValue,glm::vec2(GUISlider::x+GUISlider::w+8,GUISlider::y+(GUISlider::h-guiRect.h)),glm::vec2(textureValue->getW(),textureValue->getH()));
    SDL_GetMouseState(&guiRect.x,&guiRect.y);
    if(SDL_GetMouseState(0,0)==SDL_BUTTON_LEFT && guiRect.x>=GUISlider::x && guiRect.x<=GUISlider::x+GUISlider::w && guiRect.y>=GUISlider::y && guiRect.y<=GUISlider::y+GUISlider::h){
        GUISlider::setValue((float)(guiRect.x-GUISlider::x)/GUISlider::w);
    }
}
void GUISlider::setValue(float value){
    GUISlider::value=value;
    SDL_Surface* surf=TTF_RenderText_Blended(GUISlider::font,std::to_string((int)std::floor(GUISlider::value*100)).c_str(),{255,255,255});
    textureValue->loadFromSurface(surf);
    SDL_FreeSurface(surf);
}
void GUISlider::addValue(float value){
    GUISlider::setValue(GUISlider::getValue()+value);
}
float GUISlider::getValue(){
    return GUISlider::value;
}
