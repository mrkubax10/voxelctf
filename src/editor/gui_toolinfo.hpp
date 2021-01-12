#ifndef SRC_EDITOR_GUI_TOOLINFO_HPP
#define SRC_EDITOR_GUI_TOOLINFO_HPP
#include "../SDL2_gui/gui_component.h"
#include "../managers/resourcemanager.hpp"
#include "../SDL2_gui/gui_global.h"
class GUIToolInfo : public GUIComponent{
    int selectedTool;
    ResourceManager* resManager;
public:
    
    GUIToolInfo(int x,int y,SDL_Renderer* render,ResourceManager* man);
    void draw();
    void update(SDL_Event* ev);
};
#endif