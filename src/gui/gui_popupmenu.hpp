#ifndef GUI_POPUPMENU_H_INCLUDED
#define GUI_POPUPMENU_H_INCLUDED
#include "gui_component.hpp"
#include <vector>
#include <iostream>
#include "gui_global.hpp"
class GUIPopupmenu:public GUIComponent{
    std::vector<std::string> elements;
    std::vector<Texture*> textureElements;
    int r,g,b,hoveredElement;
    TTF_Font *font;
    bool opened,canOpen;
    GUIComponent *parentComponent;
public:
    GUIPopupmenu(std::vector<std::string> elements,TTF_Font *font,Renderer *renderer,int r=50,int g=50,int b=50);
    void update(SDL_Event *ev);
    void draw();
    void setCanOpen(bool canOpen);
    void setParentComponent(GUIComponent *parentComponent);
};
#endif // GUI_POPUPMENU_H_INCLUDED
