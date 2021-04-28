#include "gui_scrollarea.h"
GUIVerticalScrollArea::GUIVerticalScrollArea(int x,int y,int w,int h,TTF_Font *font,SDL_Renderer *render,int r,int g,int b){
    GUIVerticalScrollArea::x=x;
    GUIVerticalScrollArea::y=y;
    GUIVerticalScrollArea::w=w;
    GUIVerticalScrollArea::h=h;
    GUIVerticalScrollArea::font=font;
    GUIVerticalScrollArea::render=render;
    GUIVerticalScrollArea::r=r;
    GUIVerticalScrollArea::b=b;
    GUIVerticalScrollArea::g=g;
    GUIVerticalScrollArea::scroll=0;
}
void GUIVerticalScrollArea::update(SDL_Event *ev){
    for(int i=0; i<GUIVerticalScrollArea::components.size(); i++){
        //if(components[i]->getY()+GUIVerticalScrollArea::scroll<=GUIVerticalScrollArea::h){
            components[i]->update(ev);
        //}
    }
    if(ev->type==SDL_MOUSEWHEEL){
        GUIVerticalScrollArea::scroll-=ev->wheel.y;
        std::cout<<ev->wheel.y<<std::endl;
    }
}
void GUIVerticalScrollArea::draw(){
    guiRect.x=GUIVerticalScrollArea::x;
    guiRect.y=GUIVerticalScrollArea::y;
    guiRect.w=GUIVerticalScrollArea::w;
    guiRect.h=GUIVerticalScrollArea::h;
    SDL_SetRenderDrawColor(GUIVerticalScrollArea::render,GUIVerticalScrollArea::r,GUIVerticalScrollArea::g,GUIVerticalScrollArea::b,200);
    SDL_SetRenderDrawBlendMode(GUIVerticalScrollArea::render,SDL_BLENDMODE_BLEND);
    SDL_RenderFillRect(GUIVerticalScrollArea::render,&guiRect);
    for(int i=0; i<GUIVerticalScrollArea::components.size(); i++){
        //if(components[i]->getY()+GUIVerticalScrollArea::scroll<=GUIVerticalScrollArea::h){
            components[i]->setX(GUIVerticalScrollArea::x+components[i]->getX());
            components[i]->setY(GUIVerticalScrollArea::scroll+GUIVerticalScrollArea::y+components[i]->getY());
            components[i]->draw();
        //}
    }
}
void GUIVerticalScrollArea::add(GUIComponent *component){
    GUIVerticalScrollArea::components.push_back(component);
}
