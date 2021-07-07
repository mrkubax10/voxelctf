#include "framework/app.hpp"
#include <GL/glew.h>
#include <GL/gl.h>
App::App(std::string title,int w,int h,Uint32 hints){
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,SDL_GL_CONTEXT_PROFILE_CORE);
    App::window=SDL_CreateWindow(title.c_str(),SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,w,h,hints);
    SDL_SetWindowIcon(App::window,IMG_Load("res/textures/hud/hud_flag.png"));
    App::contextGL=SDL_GL_CreateContext(App::window);
    if(App::contextGL==0){
		std::cout<<"(Error) [OpenGL] Failed to create OpenGL context version 3.3! Try using OSMesa compiled version of game."<<std::endl;
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,"GLContext","Failed to create OpenGL context version 3.3\nTry using OSMesa compiled version of game",0);
		running=false;
	}
	SDL_GL_MakeCurrent(window,App::contextGL);
    glewExperimental=true;
	glewInit();
    SDL_GL_SetSwapInterval(0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    std::cout<<"(Log) [App] Initialized OpenGL rendering system: vendor: "<<glGetString(GL_VENDOR)<<", renderer/device: "<<glGetString(GL_RENDERER)<<", OpenGL version: "<<glGetString(GL_VERSION)<<std::endl;
    App::frame=0;
    App::running=true;
    App::settings=new Settings();
    App::resManager=new ResourceManager(this);
    App::langManager=new LanguageManager("res/translations");
    App::guiManager=new GUIManager(this);
    App::renderer=new Renderer(w,h,resManager->getShaderProgram("2dtextured"),resManager->getShaderProgram("2dcolored"));
    App::textureAtlas=new TextureAtlas(App::renderer);
    App::textureAtlas->generateTextureAtlas(resManager);
    App::chat=new Chat(5,5,renderer,resManager->getFont("default",15),this);
    App::serverConnection=new ServerConnection(chat,this);
    App::windowTexture=new RenderTexture(w,h);
}
SDL_Window* App::getWindow(){
    return window;
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
Renderer* App::getRenderer(){
    return renderer;
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
        if(App::frame!=0){
            //App::windowTexture->use();
            App::frame->render();
            //RenderTexture::useDefault(App::getWindowW(),App::getWindowH());
            //App::renderer->drawTexturedRect(App::windowTexture->getTexture(),glm::vec2(0,0),RendererFlags::FLIP_VERTICALLY);
        }
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
void App::destroy(){
    App::resManager->destroy();
    App::renderer->destroy();
    SDL_DestroyWindow(App::window);
    SDL_GL_DeleteContext(App::contextGL);
}
RenderTexture* App::getWindowRenderTexture(){
    return App::windowTexture;
}
App::~App(){}