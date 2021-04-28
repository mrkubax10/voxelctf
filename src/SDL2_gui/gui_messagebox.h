#ifndef GUI_MESSAGEBOX_H_INCLUDED
#define GUI_MESSAGEBOX_H_INCLUDED
#include <iostream>
#include <vector>
#include "gui_global.h"
#include "gui_container.h"
#include "gui_popupmenu.h"
class GUIMessagebox:public GUIContainer{
    int r,g,b,borderr,borderg,borderb;
    bool opened,draggable;
    TTF_Font *font;
    Texture *textureTitle;
    std::string title;
    int dragValueX,dragValueY;

    GUIPopupmenu *popupmenu;
public:
    GUIMessagebox(int x,int y,int w,int h,std::string title,TTF_Font *font,Renderer *renderer,bool opened=false,bool draggable=true,int r=200,int g=200,int b=200,int borderr=0,int borderg=50,int borderb=255);
    void update(SDL_Event *ev);
    void draw();
    void add(GUIComponent *component);
    void setOpened(bool opened);

    void setPopupMenu(GUIPopupmenu *popupmenu);
    bool isOpened();
};


#endif // GUI_MESSAGEBOX_H_INCLUDED
