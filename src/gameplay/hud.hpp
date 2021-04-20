#ifndef SRC_GAMEPLAY_HUD_HPP
#define SRC_GAMEPLAY_HUD_HPP
#include "../SDL2_gui/gui_component.h"
#include "player.hpp"
class App;
class HUD : public GUIComponent{
    Player* player;
    TTF_Font* font;
    SDL_Texture* textureHP;
    App* app;
public:
    HUD(SDL_Renderer* render,Player* player,TTF_Font* font,App* app);
    void draw();
    void update(SDL_Event* ev);
    void updateInfo();
};
#endif