#include "gui_component.h"
void GUIComponent::setTransition(GUIEffectTransition* transition){
    GUIComponent::transition=transition;
}
void GUIComponent::setX(int x){
    GUIComponent::x=x;
}
void GUIComponent::setY(int y){
    GUIComponent::y=y;
}
void GUIComponent::setW(int w){
    GUIComponent::w=w;
}
void GUIComponent::setH(int h){
    GUIComponent::h=h;
}
int GUIComponent::getX(){
    return GUIComponent::x;
}
int GUIComponent::getY(){
    return GUIComponent::y;
}
int GUIComponent::getW(){
    return GUIComponent::w;
}
int GUIComponent::getH(){
    return GUIComponent::h;
}
bool GUIComponent::isMouseOn(short mx,short my){
    return (mx>=GUIComponent::x && mx<=GUIComponent::x+GUIComponent::w && my>=GUIComponent::y && my<=GUIComponent::y+GUIComponent::h);
}
void GUIComponent::center(int containerW,int containerH,bool vertically,bool horizontally){
    if(horizontally)
        GUIComponent::x=(containerW-GUIComponent::w)/2;
    if(vertically)
        GUIComponent::y=(containerH-GUIComponent::h)/2;
}
void GUIComponent::setVisible(bool visible){
    GUIComponent::visible=visible;
}
bool GUIComponent::isVisible(){
    return GUIComponent::visible;
}