#include "app.hpp"
#include "GL/glew.h"
#include "GL/gl.h"
App::App(std::string title,int w,int h,Uint32 hints){
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 3 );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
    App::window=SDL_CreateWindow(title.c_str(),SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,w,h,hints);
    App::render=SDL_CreateRenderer(window,0,0);
    if(!App::render){
        
        App::render=SDL_CreateRenderer(window,0,SDL_RENDERER_SOFTWARE);
        std::cout<<"(Warn) [App] Creating software renderer"<<std::endl;
    }
    
    App::contextGL=SDL_GL_CreateContext(App::window);
    if(App::contextGL==0){
		std::cout<<"(Error) [OpenGL] Failed to create OpenGL context version 3.3! Try using OSMesa compiled version of game."<<std::endl;
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,"GLContext","Failed to create OpenGL context version 3.3\nTry using OSMesa compiled version of game",0);
		running=0;
	}
	SDL_GL_MakeCurrent(window,App::contextGL);
	glewInit();
    App::frame=0;
    App::running=true;
    App::settings=new Settings();
    App::resManager=new ResourceManager(App::render);
    App::langManager=new LanguageManager("res/translations");
    App::guiManager=new GUIManager(App::render);
    App::textureAtlas=new TextureAtlas(App::render);
    App::textureAtlas->generateTextureAtlas(resManager);
    App::gl2dRenderer=new GL2DRenderer(App::window,App::render);
    App::chat=new Chat(0,0,render,resManager->getFont("default",15),this);
    App::serverConnection=new ServerConnection(chat,this);
}
SDL_Window* App::getWindow(){
    return window;
}
SDL_Renderer* App::getRenderer(){
    return render;
}
bool App::isRunning(){
    return running;
}
void App::setRunning(bool running){
    App::running=running;
}
Frame* App::getFrame(){
    return frame;
}
SDL_Event* App::getEvent(){
    return &event;
}
ResourceManager* App::getResourceManager(){
    return resManager;
}
TextureAtlas* App::getTextureAtlas(){
    return textureAtlas;
}
GUIManager* App::getGUIManager(){
    return guiManager;
}
std::string App::getEditorMapName(){
    return App::editorMapName;
}
int App::getMouseX(){
    SDL_GetMouseState(&mouseX,0);
    return mouseX;
}
int App::getMouseY(){
    SDL_GetMouseState(0,&mouseY);
    return mouseY;
}
Settings* App::getSettings(){
    return settings;
}
GL2DRenderer* App::getGL2DRenderer(){
    return gl2dRenderer;
}
std::string App::getTitle(){
    return std::string(SDL_GetWindowTitle(App::window));
}
int App::getWindowW(){
    SDL_GetWindowSize(App::window,&windowW,&windowH);
    return windowW;
}
int App::getWindowH(){
    SDL_GetWindowSize(App::window,&windowW,&windowH);

    return windowH;
}
LanguageManager* App::getLanguageManager(){
    return langManager;
}
ServerConnection* App::getServerConnection(){
    return serverConnection;
}
Chat* App::getChat(){
    return chat;
}
void App::setFrame(Frame* frame){
    if(App::frame!=0)
        App::frame->finish();
    frame->setParent(this);
    frame->begin();
    
    App::frame=frame;
}
void App::setEditorMapName(std::string editorMapName){
    App::editorMapName=editorMapName;
}
void App::setTitle(std::string title){
    SDL_SetWindowTitle(App::window,title.c_str());
}
void App::loop(){
    while(App::running){
        if(App::frame!=0)
            App::frame->render();
    }
    App::frame->finish();
}
SDL_GLContext App::getGLContext(){
    return App::contextGL;
}
void App::setUsername(std::string username){
    App::username=username;
}
std::string App::getUsername(){
    return App::username;
}
App::~App(){}