#include "gui_toolinfo.hpp"
GUIToolInfo::GUIToolInfo(int x,int y,SDL_Renderer* render,ResourceManager* man){
    GUIToolInfo::selectedTool=0;
    GUIToolInfo::render=render;
    GUIToolInfo::resManager=man;
    GUIToolInfo::x=x;
    GUIToolInfo::y=y;
    GUIToolInfo::visible=true;
}
void GUIToolInfo::draw(){
    guiRect.x=GUIToolInfo::x;
    guiRect.y=GUIToolInfo::y;
    SDL_QueryTexture(GUIToolInfo::resManager->getTexture("editor/editorbuildtool"),0,0,&guiRect.w,&guiRect.h);
    SDL_RenderCopy(GUIToolInfo::render,GUIToolInfo::resManager->getTexture("editor/editorbuildtool"),0,&guiRect);
    guiRect.x+=guiRect.w;
    guiRect.y=GUIToolInfo::y;
    SDL_QueryTexture(GUIToolInfo::resManager->getTexture("editor/editorfilltool"),0,0,&guiRect.w,&guiRect.h);
    SDL_RenderCopy(GUIToolInfo::render,GUIToolInfo::resManager->getTexture("editor/editorfilltool"),0,&guiRect);
    guiRect.x+=guiRect.w;
    guiRect.y=GUIToolInfo::y;
    SDL_QueryTexture(GUIToolInfo::resManager->getTexture("editor/editorerasetool"),0,0,&guiRect.w,&guiRect.h);
    SDL_RenderCopy(GUIToolInfo::render,GUIToolInfo::resManager->getTexture("editor/editorerasetool"),0,&guiRect);
    guiRect.x+=guiRect.w;
    SDL_QueryTexture(GUIToolInfo::resManager->getTexture("editor/editorteam1flagtool"),0,0,&guiRect.w,&guiRect.h);
    SDL_RenderCopy(GUIToolInfo::render,GUIToolInfo::resManager->getTexture("editor/editorteam1flagtool"),0,&guiRect);
    guiRect.x+=guiRect.w;
    SDL_QueryTexture(GUIToolInfo::resManager->getTexture("editor/editorteam2flagtool"),0,0,&guiRect.w,&guiRect.h);
    SDL_RenderCopy(GUIToolInfo::render,GUIToolInfo::resManager->getTexture("editor/editorteam2flagtool"),0,&guiRect);
    guiRect.x=GUIToolInfo::x+GUIToolInfo::selectedTool*32;
    guiRect.y=GUIToolInfo::y;
    guiRect.w=32;
    guiRect.h=32;
    SDL_SetRenderDrawColor(GUIToolInfo::render,255,0,0,255);
    SDL_RenderDrawRect(GUIToolInfo::render,&guiRect);
}
void GUIToolInfo::update(SDL_Event* ev){
    if(ev->type==SDL_KEYDOWN){
        if(ev->key.keysym.scancode>=SDL_SCANCODE_1 && ev->key.keysym.scancode<=SDL_SCANCODE_5)
            GUIToolInfo::selectedTool=ev->key.keysym.scancode-SDL_SCANCODE_1;
    }
}