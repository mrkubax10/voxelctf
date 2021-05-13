#ifndef GUI_PAGELIST_H_INCLUDED
#define GUI_PAGELIST_H_INCLUDED
#include "gui_global.hpp"
#include "gui_container.hpp"
#include <vector>
#include <iostream>
struct _GUIPage{
public:
    std::vector<GUIComponent*> components;
    std::string title;
    Texture* texturePageName;
};
class GUIPagelist:public GUIContainer{
    std::vector<_GUIPage> pages;
    int selectedPage;
    int r,g,b;
    TTF_Font *font;
    int x2;
public:
    GUIPagelist(int x,int y,int w,int h,TTF_Font *font,Renderer *renderer,int selectedPage=0,int r=186,int g=255,int b=168);
    void update(SDL_Event *ev);
    void draw();
    void addPage(std::string title="Page");
    void addToPage(int page,GUIComponent* component);
    void add(GUIComponent* component){}
};


#endif // GUI_PAGELIST_H_INCLUDED
