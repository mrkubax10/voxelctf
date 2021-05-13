#ifndef SRC_NETWORK_CHAT_HPP
#define SRC_NETWORK_CHAT_HPP
#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../utils.hpp"
#include "../gui/gui_component.hpp"
#include "../render/rendertexture.hpp"
struct ChatElement{
    std::string str;
    long sendTime;
    bool timedOut;
    std::vector<Texture*> textures;
    
};
class App;
class Chat : public GUIComponent{
    std::vector<ChatElement> chatEntries;
    int posy;
    int w2,h2;
    TTF_Font* font;
    bool enteringMessage;
    std::string messageBuffer;
    App* app;
    Texture* messageTexture;
    bool textfieldOpened;
    int messageOffset=0;
    RenderTexture* chatTexture;
public:
    Chat(int x,int y,Renderer* renderer,TTF_Font* font,App* app);
    void addEntry(std::string str);
    void draw();
    void update(SDL_Event* ev);
    void updateEntries();
    void setEnteringMessage(bool enteringMessage);
    bool isEnteringMessage();
};
#endif