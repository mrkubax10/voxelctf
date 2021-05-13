#include "gui_scrollarea.hpp"
GUIVerticalScrollArea::GUIVerticalScrollArea(int x,int y,int w,int h,TTF_Font *font,Renderer *renderer,int r,int g,int b){
    GUIVerticalScrollArea::x=x;
    GUIVerticalScrollArea::y=y;
    GUIVerticalScrollArea::w=w;
    GUIVerticalScrollArea::h=h;
    GUIVerticalScrollArea::font=font;
    GUIVerticalScrollArea::renderer=renderer;
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
    renderer->drawColoredRect(glm::vec4((float)r/255.0f,(float)g/255.0f,(float)b/255.0f,1),glm::vec2(x,y),glm::vec2(w,h));
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
