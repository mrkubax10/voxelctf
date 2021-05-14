#ifndef SRC_EDITOR_GUI_TOOLINFO_HPP
#define SRC_EDITOR_GUI_TOOLINFO_HPP
#include "../gui/gui_component.hpp"
#include "../managers/resourcemanager.hpp"
#include "../gui/gui_global.hpp"
class GUIToolInfo : public GUIComponent{
    int selectedTool;
    ResourceManager* resManager;
public:
    
    GUIToolInfo(int x,int y,Renderer* renderer,ResourceManager* man);
    void draw();
    void update(SDL_Event* ev);
};
#endif