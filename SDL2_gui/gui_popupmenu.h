#ifndef GUI_POPUPMENU_H_INCLUDED
#define GUI_POPUPMENU_H_INCLUDED
#include "gui_component.h"
#include <vector>
#include <iostream>
#include "gui_global.h"
class GUIPopupmenu:public GUIComponent{
    std::vector<std::string> elements;
    std::vector<SDL_Texture*> textureElements;
    int r,g,b,hoveredElement;
    TTF_Font *font;
    bool opened,canOpen;
    GUIComponent *parentComponent;
public:
    GUIPopupmenu(std::vector<std::string> elements,TTF_Font *font,SDL_Renderer *render,int r=50,int g=50,int b=50);
    void update(SDL_Event *ev);
    void draw();
    void setCanOpen(bool canOpen);
    void setParentComponent(GUIComponent *parentComponent);
};
#endif // GUI_POPUPMENU_H_INCLUDED
