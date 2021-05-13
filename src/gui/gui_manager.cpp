#include "gui_manager.hpp"
#include "../framework/app.hpp"
GUIManager::GUIManager(App* app){
    GUIManager::app=app;
}
void GUIManager::add(GUIComponent *component){
    GUIManager::components.push_back(component);
}
void GUIManager::draw(){
    for(int i=0; i<GUIManager::components.size(); i++){
        if(GUIManager::components[i]->isVisible())
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
App* GUIManager::getApp(){
    return app;
}