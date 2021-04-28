#ifndef GUI_BUTTON_H_INCLUDED
#define GUI_BUTTON_H_INCLUDED
#include "gui_component.h"
#include "gui_global.h"
#include <iostream>
class GUIButton:public GUIComponent{
    std::string caption;
    bool hovered;
    TTF_Font *font;
    SDL_Texture *textureCaption;
    void (*callback)(void*);
    void* argument;
public:
    GUIButton(int x,int y,int w,int h,std::string caption,TTF_Font *font,SDL_Renderer *render);
    void draw();
    void update(SDL_Event *ev);
    void setSelected(bool selected);
    void setCallback(void (*callback)(void*),void* argument);
};


#endif // GUI_BUTTON_H_INCLUDED
