#include "gui_messagebox.h"
GUIMessagebox::GUIMessagebox(int x,int y,int w,int h,std::string title,TTF_Font *font,SDL_Renderer *render,bool opened,bool draggable,int r,int g,int b,int borderr,int borderg,int borderb){
    GUIMessagebox::x=x;
    GUIMessagebox::y=y;
    GUIMessagebox::w=w;
    GUIMessagebox::h=h;
    GUIMessagebox::font=font;
    GUIMessagebox::render=render;
    GUIMessagebox::opened=opened;
    GUIMessagebox::draggable=draggable;
    GUIMessagebox::r=r;
    GUIMessagebox::g=g;
    GUIMessagebox::b=b;
    GUIMessagebox::borderr=borderr;
    GUIMessagebox::borderg=borderg;
    GUIMessagebox::borderb=borderb;
    GUIMessagebox::title=title;
    GUIMessagebox::textureTitle=SDL_CreateTextureFromSurface(render,TTF_RenderUTF8_Blended(font,title.c_str(),{0,0,0}));
    GUIMessagebox::popupmenu=0;
}
void GUIMessagebox::update(SDL_Event *ev){
    if(GUIMessagebox::popupmenu!=0) {
        GUIMessagebox::popupmenu->setCanOpen(GUIMessagebox::opened);
        GUIMessagebox::popupmenu->update(ev);
    }
    for(int i=0; i<GUIMessagebox::components.size(); i++){
        GUIMessagebox::components[i]->update(ev);
    }
    if(ev->type==SDL_MOUSEBUTTONDOWN){
        if(GUIMessagebox::draggable && ev->motion.x>=GUIMessagebox::x && ev->motion.x<=GUIMessagebox::x+GUIMessagebox::w && ev->motion.y>=GUIMessagebox::y && ev->motion.y<=GUIMessagebox::y+32){
            GUIMessagebox::dragValueX=(ev->motion.x-GUIMessagebox::x);
            GUIMessagebox::dragValueY=(ev->motion.y-GUIMessagebox::y);
        }

    }
}
void GUIMessagebox::draw(){
    if(GUIMessagebox::opened){
        SDL_SetRenderDrawColor(GUIMessagebox::render,GUIMessagebox::r,GUIMessagebox::g,GUIMessagebox::b,255);
        guiRect.x=GUIMessagebox::x;
        guiRect.y=GUIMessagebox::y;
        guiRect.w=GUIMessagebox::w;
        guiRect.h=GUIMessagebox::h;
        SDL_RenderFillRect(GUIMessagebox::render,&guiRect);
        guiRect.h=16;
        SDL_SetRenderDrawColor(GUIMessagebox::render,GUIMessagebox::r,GUIMessagebox::g,GUIMessagebox::b,255);
        SDL_RenderFillRect(GUIMessagebox::render,&guiRect);
        guiRect.y=GUIMessagebox::y+16;
        SDL_SetRenderDrawColor(GUIMessagebox::render,GUIMessagebox::r-50,GUIMessagebox::g-50,GUIMessagebox::b-50,255);
        SDL_RenderFillRect(GUIMessagebox::render,&guiRect);
        SDL_QueryTexture(GUIMessagebox::textureTitle,0,0,&guiRect.w,&guiRect.h);
        guiRect.x=GUIMessagebox::x+2;
        guiRect.y=GUIMessagebox::y+(32-guiRect.h)/2;
        SDL_RenderCopy(GUIMessagebox::render,GUIMessagebox::textureTitle,0,&guiRect);
        for(int i=0; i<GUIMessagebox::components.size(); i++){
            GUIMessagebox::components[i]->draw();
        }
        if(GUIMessagebox::popupmenu!=0) GUIMessagebox::popupmenu->draw();
        SDL_GetMouseState(&guiRect.x,&guiRect.y);
        if(GUIMessagebox::draggable && SDL_GetMouseState(0,0)==SDL_BUTTON_LEFT && guiRect.x>=GUIMessagebox::x && guiRect.x<=GUIMessagebox::x+GUIMessagebox::w && guiRect.y>=GUIMessagebox::y && guiRect.y<=GUIMessagebox::y+32){
            GUIMessagebox::setX(guiRect.x-GUIMessagebox::dragValueX);
            GUIMessagebox::setY(guiRect.y-GUIMessagebox::dragValueY);
        }

    }
}
void GUIMessagebox::add(GUIComponent* component){
    GUIMessagebox::componentOriginalPositions.push_back({component->getX(),component->getY()+32});
    component->setX(GUIMessagebox::x+component->getX());
    component->setY(GUIMessagebox::y+component->getY()+32);
    GUIMessagebox::components.push_back(component);
}
void GUIMessagebox::setOpened(bool opened){
    GUIMessagebox::opened=opened;
}
void GUIMessagebox::setPopupMenu(GUIPopupmenu *popupmenu){
    GUIMessagebox::popupmenu=popupmenu;
    GUIMessagebox::popupmenu->setParentComponent(this);
}
bool GUIMessagebox::isOpened(){
    return GUIMessagebox::opened;
}
