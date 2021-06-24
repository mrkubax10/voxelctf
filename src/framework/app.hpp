#ifndef SRC_FRAMEWORK_APP_HPP
#define SRC_FRAMEWORK_APP_HPP
#include <SDL2/SDL.h>
#include <iostream>
#include "framework/frame.hpp"
#include "network/serverconnection.hpp"
#include "managers/resourcemanager.hpp"
#include "managers/languagemanager.hpp"
#include "gui/gui_manager.hpp"
#include "world/textureatlas.hpp"
#include "settings.hpp"
#include "render/renderer.hpp"
#include "render/rendertexture.hpp"
class App{
    SDL_Window* window;
    SDL_Event event;
    Frame* frame;
    bool running;
    ResourceManager* resManager;
    LanguageManager* langManager;
    ServerConnection* serverConnection;
    SDL_GLContext contextGL;
    GUIManager* guiManager;
    Settings* settings;
    TextureAtlas* textureAtlas;
    Renderer* renderer;
    RenderTexture* windowTexture;
    Chat* chat;
    int windowW,windowH,mouseX,mouseY;
    std::string editorMapName;
    std::string username;
public:
    App(std::string title,int w,int h,Uint32 hints);
    ~App();
    void loop();
    SDL_Window* getWindow();
    Frame* getFrame();
    bool isRunning();
    SDL_Event* getEvent();
    ResourceManager* getResourceManager();
    LanguageManager* getLanguageManager();
    ServerConnection* getServerConnection();
    GUIManager* getGUIManager();
    Settings* getSettings();
    TextureAtlas* getTextureAtlas();
    Renderer* getRenderer();
    Chat* getChat();
    std::string getEditorMapName();
    SDL_GLContext getGLContext();
    std::string getTitle();
    int getWindowW();
    int getWindowH();
    int getMouseX();
    int getMouseY();
    RenderTexture* getWindowRenderTexture();
    void setFrame(Frame* frame);
    void setRunning(bool running);
    void setEditorMapName(std::string editorMapName);
    void setTitle(std::string title);
    void setUsername(std::string username);
    std::string getUsername();
    void destroy();
};
#endif