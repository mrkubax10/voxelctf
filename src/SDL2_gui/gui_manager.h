#ifndef GUI_MANAGER_H_INCLUDED
#define GUI_MANAGER_H_INCLUDED
#include "gui_component.h"
#include <vector>
class GUIManager{
    std::vector<GUIComponent*> components;
    SDL_Renderer *render;
public:
    GUIManager(SDL_Renderer *render);
    void add(GUIComponent* component);
    void draw();
    void update(SDL_Event *event);
    void clear();
};


#endif // GUI_MANAGER_H_INCLUDED
