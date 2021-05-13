#include "gui_button.hpp"
GUIButton::GUIButton(int x,int y,int w,int h,std::string caption,TTF_Font *font,Renderer* renderer){
    GUIButton::caption=caption;
    GUIButton::x=x;
    GUIButton::y=y;
    GUIButton::w=w;
    GUIButton::h=h;
    GUIButton::hovered=false;
    GUIButton::selected=false;
    GUIButton::font=font;
    GUIButton::renderer=renderer;
    GUIButton::textureCaption=new Texture();
    SDL_Surface* surf=TTF_RenderUTF8_Blended(font,caption.c_str(),{255,255,255});
    textureCaption->loadFromSurface(surf);
    SDL_FreeSurface(surf);
    GUIButton::callback=0;
    GUIButton::visible=true;
}
void GUIButton::draw(){
    guiRect.x=GUIButton::x-2;
    guiRect.y=GUIButton::y-2;
    guiRect.w=GUIButton::w+4;
    guiRect.h=GUIButton::h+4;
    if(GUIButton::hovered || GUIButton::selected){
        renderer->drawColoredRect(glm::vec4(1,1,1,1),glm::vec2(x-2,y-2),glm::vec2(w+4,h+4));
    }
    renderer->drawColoredRect(glm::vec4(100.0f/255.0f,100.0f/255.0f,100.0f/255.0f,1),glm::vec2(x,y),glm::vec2(w,h));
    renderer->drawTexturedRect(textureCaption,glm::vec2(GUIButton::x+(GUIButton::w-textureCaption->getW())/2,GUIButton::y+(GUIButton::h-textureCaption->getH())/2),glm::vec2(textureCaption->getW(),textureCaption->getH()));
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