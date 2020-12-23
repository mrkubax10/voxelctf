
#include "gui_popupmenu.h"
GUIPopupmenu::GUIPopupmenu(std::vector<std::string> elements,TTF_Font *font,SDL_Renderer *render,int r,int g,int b){
    GUIPopupmenu::elements=elements;
    GUIPopupmenu::font=font;
    GUIPopupmenu::render=render;
    GUIPopupmenu::r=r;
    GUIPopupmenu::g=g;
    GUIPopupmenu::b=b;
    GUIPopupmenu::canOpen=true;
    GUIPopupmenu::w=0;
    GUIPopupmenu::h=0;
    for(int i=0; i<elements.size(); i++){
        GUIPopupmenu::textureElements.push_back(SDL_CreateTextureFromSurface(render,TTF_RenderUTF8_Blended(font,elements[i].c_str(),{255,255,255})));

        SDL_QueryTexture(GUIPopupmenu::textureElements[i],0,0,&guiRect.w,&guiRect.h);

        GUIPopupmenu::h+=guiRect.h;
        if(GUIPopupmenu::w<guiRect.w){
            GUIPopupmenu::w=guiRect.w;
        }
    }
}
void GUIPopupmenu::update(SDL_Event *ev){
    if(ev->type==SDL_MOUSEBUTTONDOWN){
        if(ev->button.button==SDL_BUTTON_RIGHT && GUIPopupmenu::parentComponent->isMouseOn(ev->motion.x,ev->motion.y)){
            GUIPopupmenu::opened=true;
            GUIPopupmenu::x=ev->motion.x;
            GUIPopupmenu::y=ev->motion.y;
        }else{
            GUIPopupmenu::opened=false;
        }
    }
}
void GUIPopupmenu::draw(){
    if(GUIPopupmenu::opened){
        guiRect.x=GUIPopupmenu::x;
        guiRect.y=GUIPopupmenu::y;
        guiRect.w=GUIPopupmenu::w;
        guiRect.h=GUIPopupmenu::h;
        SDL_SetRenderDrawColor(GUIPopupmenu::render,GUIPopupmenu::r,GUIPopupmenu::g,GUIPopupmenu::b,255);
        SDL_RenderFillRect(GUIPopupmenu::render,&guiRect);
        for(int i=0; GUIPopupmenu::elements.size(); i++){

            SDL_QueryTexture(GUIPopupmenu::textureElements[i],0,0,&guiRect.w,&guiRect.h);
            SDL_RenderCopy(GUIPopupmenu::render,GUIPopupmenu::textureElements[i],0,&guiRect);
            guiRect.y+=guiRect.h;
        }
    }
}
void GUIPopupmenu::setCanOpen(bool canOpen){
    GUIPopupmenu::canOpen=canOpen;
}
void GUIPopupmenu::setParentComponent(GUIComponent* parentComponent){
    GUIPopupmenu::parentComponent=parentComponent;
}
