#include "gui_button.h"
GUIButton::GUIButton(int x,int y,int w,int h,std::string caption,TTF_Font *font,SDL_Renderer *render){
    GUIButton::caption=caption;
    GUIButton::x=x;
    GUIButton::y=y;
    GUIButton::w=w;
    GUIButton::h=h;
    GUIButton::hovered=false;
    GUIButton::selected=false;
    GUIButton::font=font;
    GUIButton::render=render;
    GUIButton::textureCaption=SDL_CreateTextureFromSurface(render,TTF_RenderUTF8_Blended(font,caption.c_str(),{255,255,255}));
    GUIButton::callback=0;
}
void GUIButton::draw(){
    guiRect.x=GUIButton::x-2;
    guiRect.y=GUIButton::y-2;
    guiRect.w=GUIButton::w+4;
    guiRect.h=GUIButton::h+4;
    if(GUIButton::hovered || GUIButton::selected){SDL_SetRenderDrawColor(GUIButton::render,255,255,255,255);SDL_RenderFillRect(render,&guiRect);}
    SDL_SetRenderDrawColor(GUIButton::render,100,100,100,255);
    guiRect.x=GUIButton::x;
    guiRect.y=GUIButton::y;
    guiRect.w=GUIButton::w;
    guiRect.h=GUIButton::h;
    SDL_RenderFillRect(GUIButton::render,&guiRect);
    SDL_QueryTexture(GUIButton::textureCaption,0,0,&guiRect.w,&guiRect.h);
    guiRect.x=GUIButton::x+(GUIButton::w-guiRect.w)/2;
    guiRect.y=GUIButton::y+(GUIButton::h-guiRect.h)/2;
    SDL_RenderCopy(GUIButton::render,GUIButton::textureCaption,0,&guiRect);
}
void GUIButton::update(SDL_Event *ev){
    if(ev->type==SDL_MOUSEMOTION){
        GUIButton::hovered=(ev->motion.x>=GUIButton::x && ev->motion.x<=GUIButton::x+GUIButton::w && ev->motion.y>=GUIButton::y && ev->motion.y<=GUIButton::y+GUIButton::h);
    }
    if(ev->type==SDL_MOUSEBUTTONDOWN){
        if(ev->button.button==SDL_BUTTON_LEFT){
            if(GUIButton::isMouseOn(ev->motion.x,ev->motion.y)){
                if(GUIButton::callback!=0)
                    (*callback)(argument);
            }
        }
    }
}
void GUIButton::setSelected(bool selected){
    GUIButton::selected=selected;
}
void GUIButton::setCallback(void (*f)(void*),void* argument){
    GUIButton::callback=f;
    GUIButton::argument=argument;
}