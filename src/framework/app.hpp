#ifndef SRC_FRAMEWORK_APP_HPP
#define SRC_FRAMEWORK_APP_HPP
#include <SDL2/SDL.h>
#include <iostream>
#include "frame.hpp"
#include "../network/serverconnection.hpp"
#include "../managers/resourcemanager.hpp"
#include "../managers/languagemanager.hpp"
#include "../SDL2_gui/SDLGui.h"
#include "../world/textureatlas.hpp"
#include "../settings.hpp"
#include "../render/gl2drenderer.hpp"
class App{
    SDL_Window* window;
    SDL_Event event;
    Frame* frame;
    SDL_Renderer* render;
    bool running;
    ResourceManager* resManager;
    LanguageManager* langManager;
    ServerConnection* serverConnection;
    SDL_GLContext contextGL;
    GUIManager* guiManager;
    Settings* settings;
    TextureAtlas* textureAtlas;
    GL2DRenderer* gl2dRenderer;
    Chat* chat;
    int windowW,windowH,mouseX,mouseY;
    std::string editorMapName;
public:
    App(std::string title,int w,int h,Uint32 hints);
    ~App();
    void loop();
    SDL_Window* getWindow();
    SDL_Renderer* getRenderer();
    Frame* getFrame();
    bool isRunning();
    SDL_Event* getEvent();
    ResourceManager* getResourceManager();
    LanguageManager* getLanguageManager();
    ServerConnection* getServerConnection();
    GUIManager* getGUIManager();
    Settings* getSettings();
    TextureAtlas* getTextureAtlas();
    GL2DRenderer* getGL2DRenderer();
    Chat* getChat();
    std::string getEditorMapName();
    std::string getTitle();
    int getWindowW();
    int getWindowH();
    int getMouseX();
    int getMouseY();
    void setFrame(Frame* frame);
    void setRunning(bool running);
    void setEditorMapName(std::string editorMapName);
    void setTitle(std::string title);
    
};
#endif