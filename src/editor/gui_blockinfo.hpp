#ifndef SRC_SDL2_GUI_GUI_BLOCKINFO_HPP
#define SRC_SDL2_GUI_GUI_BLOCKINFO_HPP
#include "../gui/gui_component.hpp"
#include "../world/block.hpp"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../managers/resourcemanager.hpp"
#include "../utils.hpp"
#include "../gui/gui_global.hpp"
extern std::string blockNames[];
class GUIBlockInfo : public GUIComponent{
    TTF_Font* font;
    int currentBlockId;
    Texture* textureBlockName;
    ResourceManager* resManager;
public:
    GUIBlockInfo(int x,int y,TTF_Font* font,Renderer* render);
    void update(SDL_Event* ev);
    void draw();
};
#endif