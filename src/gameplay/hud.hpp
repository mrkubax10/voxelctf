#ifndef SRC_GAMEPLAY_HUD_HPP
#define SRC_GAMEPLAY_HUD_HPP
#include "../gui/gui_component.hpp"
#include "player.hpp"
class App;
class HUD : public GUIComponent{
    Player* player;
    TTF_Font* font;
    Texture* textureHP;
    App* app;
public:
    HUD(Renderer* renderer,Player* player,TTF_Font* font,App* app);
    void draw();
    void update(SDL_Event* ev);
    void updateInfo();
};
#endif