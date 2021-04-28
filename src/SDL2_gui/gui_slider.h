#ifndef GUI_SLIDER_H_INCLUDED
#define GUI_SLIDER_H_INCLUDED
#include <iostream>
#include "gui_global.h"
#include "gui_component.h"
class GUISlider:public GUIComponent{
    float value;
    TTF_Font *font;
    Texture* textureValue;
public:
    GUISlider(int x,int y,int w,int h,Renderer* renderer,TTF_Font *font,float value=0);
    void update(SDL_Event *ev);
    void draw();
    void setValue(float value);
    void addValue(float value);
    float getValue();
};


#endif // GUI_SLIDER_H_INCLUDED
