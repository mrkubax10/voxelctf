#ifndef GUI_COMBOBOX_H_INCLUDED
#define GUI_COMBOBOX_H_INCLUDED
#include "gui_global.h"
#include <iostream>
#include <vector>
#include "gui_component.h"
class GUICombobox:public GUIComponent{
    std::vector<std::string> elements;
    int selectedElement;
    Texture *textureSelectedElement;
    bool expanded;
    int w2,h2;
    std::vector<Texture*> textureElements;
    int listh;
    TTF_Font *font;
    int r,g,b;
    int listr,listg,listb;
public:
    GUICombobox(int x,int y,std::vector<std::string> elements,TTF_Font *font,Renderer* renderer,int selectedElement=0,int r=255,int g=255,int b=255,int listr=200,int listg=200,int listb=220);
    void update(SDL_Event *ev);
    void draw();
    void setSelectedElement(int selectedElement);
    int getSelectedElement();
    std::string getSelectedElementName();
};


#endif // GUI_COMBOBOX_H_INCLUDED
