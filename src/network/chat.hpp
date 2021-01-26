#ifndef SRC_NETWORK_CHAT_HPP
#define SRC_NETWORK_CHAT_HPP
#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../utils.hpp"
#include "../SDL2_gui/SDLGui.h"
class Chat : public GUIComponent{
    std::vector<std::string> chatEntries;
    std::vector<SDL_Texture*> chatEntryTextures;
    SDL_Renderer* render;
    int posy;
    int w2,h2;
    TTF_Font* font;
public:
    Chat(int x,int y,SDL_Renderer* render,TTF_Font* font);
    void addEntry(std::string str);
    void draw();
    void update(SDL_Event* ev);
};
#endif