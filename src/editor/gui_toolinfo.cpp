#include "gui_toolinfo.hpp"
GUIToolInfo::GUIToolInfo(int x,int y,Renderer* renderer,ResourceManager* man){
    GUIToolInfo::selectedTool=0;
    GUIToolInfo::renderer=renderer;
    GUIToolInfo::resManager=man;
    GUIToolInfo::x=x;
    GUIToolInfo::y=y;
    GUIToolInfo::visible=true;
}
void GUIToolInfo::draw(){
    renderer->drawTexturedRect(GUIToolInfo::resManager->getNativeTexture("editor/editorbuildtool"),glm::vec2(x,y),glm::vec2(GUIToolInfo::resManager->getNativeTexture("editor/editorbuildtool")->getW(),GUIToolInfo::resManager->getNativeTexture("editor/editorbuildtool")->getH()));
    renderer->drawTexturedRect(GUIToolInfo::resManager->getNativeTexture("editor/editorfilltool"),glm::vec2(x+32,y),glm::vec2(32,32));
    renderer->drawTexturedRect(GUIToolInfo::resManager->getNativeTexture("editor/editorerasetool"),glm::vec2(x+32*2,y),glm::vec2(32,32));
    renderer->drawTexturedRect(GUIToolInfo::resManager->getNativeTexture("editor/editorteam1flagtool"),glm::vec2(x+32*3,y),glm::vec2(32,32));
    renderer->drawTexturedRect(GUIToolInfo::resManager->getNativeTexture("editor/editorteam2tool"),glm::vec2(x+32*4,y),glm::vec2(32,32));
}
void GUIToolInfo::update(SDL_Event* ev){
    if(ev->type==SDL_KEYDOWN){
        if(ev->key.keysym.scancode>=SDL_SCANCODE_1 && ev->key.keysym.scancode<=SDL_SCANCODE_5)
            GUIToolInfo::selectedTool=ev->key.keysym.scancode-SDL_SCANCODE_1;
    }
}