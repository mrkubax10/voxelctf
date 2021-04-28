#ifndef GUI_CHECKBOX_H_INCLUDED
#define GUI_CHECKBOX_H_INCLUDED
#include <iostream>
#include "gui_global.h"
#include "gui_component.h"
class GUICheckbox:public GUIComponent{
    std::string text;
    bool checked;
    int r,g,b;
    int chr,chg,chb;
    Texture* textureText;
    TTF_Font* font;
public:
    GUICheckbox(int x,int y,std::string text,TTF_Font *font,Renderer* renderer,int r=255,int g=255,int b=255,int chr=0,int chg=200,int chb=255);
    void update(SDL_Event *ev);
    void draw();
    void setChecked(bool checked);
    bool isChecked();
};


#endif // GUI_CHECKBOX_H_INCLUDED
