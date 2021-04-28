#ifndef GUI_SCROLLAREA_H_INCLUDED
#define GUI_SCROLLAREA_H_INCLUDED
#include <iostream>
#include <vector>
#include "gui_global.h"
#include "gui_component.h"
class GUIVerticalScrollArea:public GUIComponent{
    std::vector<GUIComponent*> components;
    int w,h,r,g,b;
    SDL_Renderer *render;
    TTF_Font *font;
    int scroll;
public:
    GUIVerticalScrollArea(int x,int y,int w,int h,TTF_Font *font,SDL_Renderer *render,int r=150,int g=150,int b=150);
    void update(SDL_Event *ev);
    void draw();
    void add(GUIComponent* component);
};


#endif // GUI_SCROLLAREA_H_INCLUDED