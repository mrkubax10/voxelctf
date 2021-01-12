#include "gui_toolinfo.hpp"
GUIToolInfo::GUIToolInfo(int x,int y,SDL_Renderer* render,ResourceManager* man){
    GUIToolInfo::selectedTool=0;
    GUIToolInfo::render=render;
    GUIToolInfo::resManager=man;
    GUIToolInfo::x=x;
    GUIToolInfo::y=y;
}
void GUIToolInfo::draw(){
    guiRect.x=GUIToolInfo::x;
    guiRect.y=GUIToolInfo::y;
    SDL_QueryTexture(GUIToolInfo::resManager->getTexture("editor/build_tool"),0,0,&guiRect.w,&guiRect.h);
    SDL_RenderCopy(GUIToolInfo::render,GUIToolInfo::resManager->getTexture("editor/build_tool"),0,&guiRect);
    guiRect.x=GUIToolInfo::x+guiRect.w;
    guiRect.y=GUIToolInfo::y;
    SDL_QueryTexture(GUIToolInfo::resManager->getTexture("editor/fill_tool"),0,0,&guiRect.w,&guiRect.h);
    SDL_RenderCopy(GUIToolInfo::render,GUIToolInfo::resManager->getTexture("editor/fill_tool"),0,&guiRect);
    guiRect.x=GUIToolInfo::x+GUIToolInfo::selectedTool*16;
    guiRect.y=GUIToolInfo::y;
    guiRect.w=17;
    guiRect.h=17;
    SDL_SetRenderDrawColor(GUIToolInfo::render,255,0,0,255);
    SDL_RenderDrawRect(GUIToolInfo::render,&guiRect);
}
void GUIToolInfo::update(SDL_Event* ev){
    if(ev->type==SDL_KEYDOWN){
        if(ev->key.keysym.scancode>=SDL_SCANCODE_1 && ev->key.keysym.scancode<=SDL_SCANCODE_2)
            GUIToolInfo::selectedTool=ev->key.keysym.scancode-SDL_SCANCODE_1;
    }
}