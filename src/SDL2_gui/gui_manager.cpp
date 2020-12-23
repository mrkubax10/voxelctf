#include "gui_manager.h"
GUIManager::GUIManager(SDL_Renderer *render){
    GUIManager::render=render;
}
void GUIManager::add(GUIComponent *component){
    GUIManager::components.push_back(component);
}
void GUIManager::draw(){
    for(int i=0; i<GUIManager::components.size(); i++){
        GUIManager::components[i]->draw();
    }
}
void GUIManager::update(SDL_Event *event){
    for(int i=0; i<GUIManager::components.size(); i++){
        GUIManager::components[i]->update(event);
    }
}
void GUIManager::clear(){
	components.clear();
}
