#ifndef GUI_PROGRESSBAR_H_INCLUDED
#define GUI_PROGRESSBAR_H_INCLUDED
#include <iostream>
#include "gui_global.h"
#include "gui_component.h"
class GUIProgressbar:public GUIComponent{
    int r,g,b,r1,g1,b1;
    Renderer *renderer;
    TTF_Font *font;
    Texture *texturePercent;
    int percents;
public:
    GUIProgressbar(int x,int y,int w,int h,TTF_Font *font,Renderer *renderer,int percents=0,int r=50,int g=50,int b=50,int r1=0,int g1=205,int b1=0);
    void update(SDL_Event *ev);
    void draw();
    void setPercentage(int percents);
    void addPercents(int percents);
    int getPercentage();

};

#endif // GUI_PROGRESSBAR_H_INCLUDED
