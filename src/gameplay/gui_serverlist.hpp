#ifndef SRC_GAMEPLAY_GUI_SERVERLIST_HPP
#define SRC_GAMEPLAY_GUI_SERVERLIST_HPP
#include "../gui/gui_component.hpp"
#include <vector>
#include <iostream>
#include <SDL2/SDL_ttf.h>
#include "../managers/languagemanager.hpp"
#include "../gui/gui_global.hpp"
#include "../utils.hpp"
#include "../gui/gui_textbox.hpp"
#define GUI_SERVERLIST_ENTRY_HEIGHT 18
class GUIServerlist : public GUIComponent{
    struct ListEntry{
        std::string name,ip;
        Texture* textureName,*textureIP;
    };
    Texture* titleServerName,*titleServerIP;
    std::vector<ListEntry> entries;
    int selectedEntry;
    TTF_Font* font;
    int titleIPX;
    int titleNameX;
    GUITextbox* textboxIP;
    void loadListFromFile();
public:
    GUIServerlist(int x,int y,int w,int h,TTF_Font* font,LanguageManager* langManager,Renderer* renderer,GUITextbox* textboxIP);
    void update(SDL_Event* ev);
    void draw();
    bool isMouseOnList(int mx,int my);
    void addServer(std::string name,std::string ip);
    void saveListToFile();
};
#endif