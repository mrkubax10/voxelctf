#ifndef GUI_COMPONENT_H_INCLUDED
#define GUI_COMPONENT_H_INCLUDED
#include <SDL2/SDL.h>
#include "gui_effect_transition.h"
class GUIComponent{
protected:
    int x,y,w,h;
    bool selected;
    SDL_Renderer *render;
    GUIEffectTransition* transition;
public:
    virtual void draw()=0;
    virtual void update(SDL_Event *ev)=0;
    void setTransition(GUIEffectTransition* transition);
    void setX(int x);
    void setY(int y);

    int getX();
    int getY();
    int getW();
    int getH();
    bool isMouseOn(short mx,short my);
    void center(int containerW,int containerH,bool vertically=true,bool horizontally=true);
};


#endif // GUI_COMPONENT_H_INCLUDED