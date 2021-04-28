#ifndef GUI_TEXTBOX_H_INCLUDED
#define GUI_TEXTBOX_H_INCLUDED
#include <iostream>
#include "gui_global.h"
#include "gui_component.h"
#include "../render/texture.hpp"
class GUITextbox:public GUIComponent{
    std::string buffer;
    Texture* textureBuffer;
    TTF_Font *font;
    bool active;
    int r,g,b;
public:
    GUITextbox(int x,int y,int w,int h,Renderer* renderer,TTF_Font *font,std::string startText="",int r=100,int g=100,int b=100);
    void draw();
    void update(SDL_Event *ev);
    std::string getText();
    void setText(std::string text);
};


#endif // GUI_TEXTBOX_H_INCLUDED
