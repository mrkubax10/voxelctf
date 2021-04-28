#include "gui_pagelist.h"
GUIPagelist::GUIPagelist(int x,int y,int w,int h,TTF_Font *font,SDL_Renderer *render,int selectedPage,int r,int g,int b){
    GUIPagelist::x=x;
    GUIPagelist::y=y;
    GUIPagelist::w=w;
    GUIPagelist::h=h;
    GUIPagelist::font=font;
    GUIPagelist::render=render;
    GUIPagelist::selectedPage=selectedPage;
    GUIPagelist::r=r;
    GUIPagelist::g=g;
    GUIPagelist::b=b;
}
void GUIPagelist::update(SDL_Event *ev){
    if(ev->type==SDL_MOUSEBUTTONDOWN){
        if(ev->button.button==SDL_BUTTON_LEFT){
            guiRect.x=GUIPagelist::x;
            guiRect.y=GUIPagelist::y;
            for(int i=0; i<GUIPagelist::pages.size(); i++){
                SDL_QueryTexture(GUIPagelist::pages[i].texturePageName,0,0,&guiRect.w,&guiRect.h);
                if(ev->motion.x>=guiRect.x && ev->motion.x<=guiRect.x+guiRect.w && ev->motion.y>=guiRect.y && ev->motion.y<=guiRect.y+guiRect.h){
                    GUIPagelist::selectedPage=i;
                    break;
                }
                guiRect.x+=guiRect.w;
            }
        }
    }
    for(int i=0; i<GUIPagelist::pages[selectedPage].components.size(); i++){
        GUIPagelist::pages[selectedPage].components[i]->update(ev);
    }
}
void GUIPagelist::draw(){
    guiRect.x=GUIPagelist::x;
    guiRect.y=GUIPagelist::y;
    guiRect.w=GUIPagelist::w;
    guiRect.h=GUIPagelist::h;
    GUIPagelist::x2=GUIPagelist::x;
    SDL_SetRenderDrawColor(GUIPagelist::render,GUIPagelist::r,GUIPagelist::g,GUIPagelist::b,255);
    SDL_RenderFillRect(GUIPagelist::render,&guiRect);
    for(int i=0; i<GUIPagelist::pages.size(); i++){
        guiRect.y=GUIPagelist::y;
        guiRect.x=GUIPagelist::x2;
        SDL_QueryTexture(GUIPagelist::pages[i].texturePageName,0,0,&guiRect.w,&guiRect.h);
        if(GUIPagelist::selectedPage==i)SDL_SetRenderDrawColor(GUIPagelist::render,GUIPagelist::r-100,GUIPagelist::g-100,GUIPagelist::b-100,255);
        else SDL_SetRenderDrawColor(GUIPagelist::render,GUIPagelist::r-50,GUIPagelist::g-50,GUIPagelist::b-50,255);
        SDL_RenderFillRect(GUIPagelist::render,&guiRect);
        SDL_SetRenderDrawColor(GUIPagelist::render,255,255,255,255);
        SDL_RenderDrawRect(GUIPagelist::render,&guiRect);
        SDL_RenderCopy(GUIPagelist::render,GUIPagelist::pages[i].texturePageName,0,&guiRect);
        GUIPagelist::x2+=guiRect.w;

    }
    for(int i=0; i<GUIPagelist::pages[GUIPagelist::selectedPage].components.size(); i++){
            GUIPagelist::pages[GUIPagelist::selectedPage].components[i]->draw();
    }
}
void GUIPagelist::addPage(std::string title){
    GUIPagelist::pages.push_back(_GUIPage());
    GUIPagelist::pages.back().title=title;
    GUIPagelist::pages.back().texturePageName=SDL_CreateTextureFromSurface(GUIPagelist::render,TTF_RenderUTF8_Blended(GUIPagelist::font,GUIPagelist::pages.back().title.c_str(),{0,0,0}));
}
void GUIPagelist::addToPage(int page,GUIComponent* component){
    component->setX(component->getX()+GUIPagelist::x);
    component->setY(component->getY()+GUIPagelist::y);
    GUIPagelist::pages[page].components.push_back(component);
}
