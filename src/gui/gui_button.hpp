#ifndef GUI_BUTTON_H_INCLUDED
#define GUI_BUTTON_H_INCLUDED
#include "gui_component.hpp"
#include "gui_global.hpp"
#include <iostream>
#include <functional>
class GUIButton:public GUIComponent{
    std::string caption;
    bool hovered;
    TTF_Font *font;
    Texture *textureCaption;
    std::function<void (void*)> callback;
    void* argument;
public:
    GUIButton(int x,int y,int w,int h,std::string caption,TTF_Font *font,Renderer* renderer);
    void draw();
    void update(SDL_Event *ev);
    void setSelected(bool selected);
    void setCallback(std::function<void (void*)> callback,void* argument);
};


#endif // GUI_BUTTON_H_INCLUDED
