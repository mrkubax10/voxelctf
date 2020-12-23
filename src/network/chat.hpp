#ifndef SRC_NETWORK_CHAT_HPP
#define SRC_NETWORK_CHAT_HPP
#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../utils.hpp"
class Chat{
    std::vector<std::string> chatEntries;
    std::vector<SDL_Texture*> chatEntryTextures;
    SDL_Renderer* render;
    int w,h;
    int posy;
    TTF_Font* font;
public:
    Chat(SDL_Renderer* render,TTF_Font* font);
    void addEntry(std::string str);
    void draw(int windowW,int windowH);
};
#endif