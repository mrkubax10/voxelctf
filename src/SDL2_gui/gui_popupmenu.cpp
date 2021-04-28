
#include "gui_popupmenu.h"
GUIPopupmenu::GUIPopupmenu(std::vector<std::string> elements,TTF_Font *font,Renderer *renderer,int r,int g,int b){
    GUIPopupmenu::elements=elements;
    GUIPopupmenu::font=font;
    GUIPopupmenu::renderer=renderer;
    GUIPopupmenu::r=r;
    GUIPopupmenu::g=g;
    GUIPopupmenu::b=b;
    GUIPopupmenu::canOpen=true;
    GUIPopupmenu::w=0;
    GUIPopupmenu::h=0;
    for(int i=0; i<elements.size(); i++){
        GUIPopupmenu::textureElements.push_back(new Texture());
        SDL_Surface* surf=TTF_RenderUTF8_Blended(font,elements[i].c_str(),{255,255,255});
        textureElements.back()->loadFromSurface(surf);
        SDL_FreeSurface(surf);
        GUIPopupmenu::h+=textureElements[i]->getH();
        if(GUIPopupmenu::w<textureElements[i]->getW()){
            GUIPopupmenu::w=textureElements[i]->getW();
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
        guiRect.y=GUIPopupmenu::y;
        renderer->drawColoredRect(glm::vec4((float)r/255.0f,(float)g/255.0f,(float)b/255.0f,1),glm::vec2(x,y),glm::vec2(w,h));
        for(int i=0; GUIPopupmenu::elements.size(); i++){
            renderer->drawTexturedRect(textureElements[i],glm::vec2(x,guiRect.y),glm::vec2(textureElements[i]->getW(),textureElements[i]->getH()));
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
