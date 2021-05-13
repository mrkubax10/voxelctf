#include "gui_pagelist.hpp"
GUIPagelist::GUIPagelist(int x,int y,int w,int h,TTF_Font *font,Renderer *renderer,int selectedPage,int r,int g,int b){
    GUIPagelist::x=x;
    GUIPagelist::y=y;
    GUIPagelist::w=w;
    GUIPagelist::h=h;
    GUIPagelist::font=font;
    GUIPagelist::renderer=renderer;
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
                if(ev->motion.x>=guiRect.x && ev->motion.x<=guiRect.x+pages[i].texturePageName->getW() && ev->motion.y>=guiRect.y && ev->motion.y<=guiRect.y+pages[i].texturePageName->getH()){
                    GUIPagelist::selectedPage=i;
                    break;
                }
                guiRect.x+=pages[i].texturePageName->getW();
            }
        }
    }
    for(int i=0; i<GUIPagelist::pages[selectedPage].components.size(); i++){
        GUIPagelist::pages[selectedPage].components[i]->update(ev);
    }
}
void GUIPagelist::draw(){
    GUIPagelist::x2=GUIPagelist::x;
    renderer->drawColoredRect(glm::vec4((float)r/255.0f,(float)g/255.0f,(float)b/255.0f,1),glm::vec2(x,y),glm::vec2(w,h));
    for(int i=0; i<GUIPagelist::pages.size(); i++){
        if(GUIPagelist::selectedPage==i)
            renderer->drawColoredRect(glm::vec4((float)(GUIPagelist::r-100)/255.0f,(float)(GUIPagelist::g-100)/255.0f,(float)(GUIPagelist::b-100)/255.0f,1),glm::vec2(x2,y),glm::vec2(pages[i].texturePageName->getW(),pages[i].texturePageName->getH()));
        else
            renderer->drawColoredRect(glm::vec4((float)(GUIPagelist::r-50)/255.0f,(float)(GUIPagelist::g-50)/255.0f,(float)(GUIPagelist::b-50)/255.0f,1),glm::vec2(x2,y),glm::vec2(pages[i].texturePageName->getW(),pages[i].texturePageName->getH()));

        GUIPagelist::x2+=guiRect.w;

    }
    for(int i=0; i<GUIPagelist::pages[GUIPagelist::selectedPage].components.size(); i++){
            GUIPagelist::pages[GUIPagelist::selectedPage].components[i]->draw();
    }
}
void GUIPagelist::addPage(std::string title){
    GUIPagelist::pages.push_back(_GUIPage());
    GUIPagelist::pages.back().title=title;
    SDL_Surface* surf=TTF_RenderUTF8_Blended(GUIPagelist::font,GUIPagelist::pages.back().title.c_str(),{0,0,0});
    GUIPagelist::pages.back().texturePageName=new Texture();
    GUIPagelist::pages.back().texturePageName->loadFromSurface(surf);

}
void GUIPagelist::addToPage(int page,GUIComponent* component){
    component->setX(component->getX()+GUIPagelist::x);
    component->setY(component->getY()+GUIPagelist::y);
    GUIPagelist::pages[page].components.push_back(component);
}
