#ifndef SRC_GAMEPLAY_GUI_SERVERLIST_HPP
#define SRC_GAMEPLAY_GUI_SERVERLIST_HPP
#include "../SDL2_gui/gui_component.h"
#include <vector>
#include <iostream>
#include <SDL2/SDL_ttf.h>
#include "../managers/languagemanager.hpp"
#include "../SDL2_gui/gui_global.h"
#define GUI_SERVERLIST_ENTRY_HEIGHT 20
class GUIServerlist : public GUIComponent{
    struct ListEntry{
        std::string name,ip;
        SDL_Texture* textureName,*textureIP;
    };
    SDL_Texture* titleServerName,*titleServerIP;
    std::vector<ListEntry> entries;
    int selectedEntry;
    TTF_Font* font;
    int titleIPX;
    int titleNameX;
    void loadListFromFile();
public:
    GUIServerlist(int x,int y,int w,int h,TTF_Font* font,LanguageManager* langManager,SDL_Renderer* render);
    void update(SDL_Event* ev);
    void draw();
    bool isMouseOnList(int mx,int my);
};
#endif