#ifndef SRC_SDL2_GUI_GUI_IMAGE_HPP
#define SRC_SDL2_GUI_GUI_IMAGE_HPP
#include "gui_component.h"
#include <SDL2/SDL.h>
#include "gui_global.h"
class GUIImage : public GUIComponent{
    SDL_Texture* texture;
public:
    GUIImage(int x,int y,SDL_Renderer* render,SDL_Texture* texture);
    void update(SDL_Event* ev);
    void draw();
    void setSize(int w,int h);
    
};
#endif