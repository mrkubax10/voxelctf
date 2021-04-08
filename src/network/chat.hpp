#ifndef SRC_NETWORK_CHAT_HPP
#define SRC_NETWORK_CHAT_HPP
#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../utils.hpp"
#include "../SDL2_gui/SDLGui.h"
struct ChatElement{
    std::string str;
    long sendTime;
    std::vector<SDL_Texture*> textures;
};
class App;
class Chat : public GUIComponent{
    std::vector<ChatElement> chatEntries;
    SDL_Renderer* render;
    int posy;
    int w2,h2;
    TTF_Font* font;
    bool enteringMessage;
    std::string messageBuffer;
    App* app;
    SDL_Texture* messageTexture;
    bool textfieldOpened;
public:
    Chat(int x,int y,SDL_Renderer* render,TTF_Font* font,App* app);
    void addEntry(std::string str);
    void draw();
    void update(SDL_Event* ev);
    void updateEntries();
    void setEnteringMessage(bool enteringMessage);
    bool isEnteringMessage();
};
#endif