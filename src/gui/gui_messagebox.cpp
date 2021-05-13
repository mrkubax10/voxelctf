#include "gui_messagebox.hpp"
GUIMessagebox::GUIMessagebox(int x,int y,int w,int h,std::string title,TTF_Font *font,Renderer *renderer,bool opened,bool draggable,int r,int g,int b,int borderr,int borderg,int borderb){
    GUIMessagebox::x=x;
    GUIMessagebox::y=y;
    GUIMessagebox::w=w;
    GUIMessagebox::h=h;
    GUIMessagebox::font=font;
    GUIMessagebox::renderer=renderer;
    GUIMessagebox::opened=opened;
    GUIMessagebox::draggable=draggable;
    GUIMessagebox::r=r;
    GUIMessagebox::g=g;
    GUIMessagebox::b=b;
    GUIMessagebox::borderr=borderr;
    GUIMessagebox::borderg=borderg;
    GUIMessagebox::borderb=borderb;
    GUIMessagebox::title=title;
    GUIMessagebox::textureTitle=new Texture();
    SDL_Surface* surf=TTF_RenderUTF8_Blended(font,title.c_str(),{0,0,0});
    textureTitle->loadFromSurface(surf);
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
        renderer->drawColoredRect(glm::vec4(0.4f,0.4f,0.4f,0.9f),glm::vec2(x,y),glm::vec2(w,h));
        renderer->drawTexturedRect(textureTitle,glm::vec2(x+2,y+2),glm::vec2(textureTitle->getW(),textureTitle->getH()));
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
