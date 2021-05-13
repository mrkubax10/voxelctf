#ifndef GUI_SCROLLAREA_H_INCLUDED
#define GUI_SCROLLAREA_H_INCLUDED
#include <iostream>
#include <vector>
#include "gui_global.hpp"
#include "gui_component.hpp"
class GUIVerticalScrollArea:public GUIComponent{
    std::vector<GUIComponent*> components;
    int w,h,r,g,b;
    Renderer *renderer;
    TTF_Font *font;
    int scroll;
public:
    GUIVerticalScrollArea(int x,int y,int w,int h,TTF_Font *font,Renderer *renderer,int r=150,int g=150,int b=150);
    void update(SDL_Event *ev);
    void draw();
    void add(GUIComponent* component);
};


#endif // GUI_SCROLLAREA_H_INCLUDED
