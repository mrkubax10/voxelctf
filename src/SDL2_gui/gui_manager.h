#ifndef GUI_MANAGER_H_INCLUDED
#define GUI_MANAGER_H_INCLUDED
#include "gui_component.h"
#include <vector>
class App;
class GUIManager{
    std::vector<GUIComponent*> components;
    App* app;
public:
    GUIManager(App* app);
    void add(GUIComponent* component);
    void draw();
    void update(SDL_Event *event);
    void clear();
    App* getApp();
};


#endif // GUI_MANAGER_H_INCLUDED
