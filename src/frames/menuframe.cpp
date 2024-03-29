#include "menuframe.hpp"
#include "../framework/app.hpp"
#include "frameconstants.hpp"
#include <GL/glew.h>
#include <GL/gl.h>
void MenuFrame::begin(){
    MenuFrame::app->setTitle("VoxelCTF");
    //Mix_PlayMusic(MenuFrame::app->getResourceManager()->getMusic("menu"),-1);
    MenuFrame::app->getGUIManager()->clear();
    imageLogo=new GUIImage(0,0,app->getRenderer(),app->getResourceManager()->getNativeTexture("logo_full"));
    buttonPlay=new GUIButton(15,100,200,50,app->getLanguageManager()->getFromCurrentLanguage("menu_play"),app->getResourceManager()->getFont("default",20),app->getRenderer());
	buttonFastGame=new GUIButton(15,170,200,50,app->getLanguageManager()->getFromCurrentLanguage("menu_fastgame"),app->getResourceManager()->getFont("default",20),app->getRenderer());
	buttonEditor=new GUIButton(15,240,200,50,app->getLanguageManager()->getFromCurrentLanguage("menu_editor"),app->getResourceManager()->getFont("default",20),app->getRenderer());
	buttonSettings=new GUIButton(15,310,200,50,app->getLanguageManager()->getFromCurrentLanguage("menu_settings"),app->getResourceManager()->getFont("default",20),app->getRenderer());
	buttonAuthors=new GUIButton(15,380,200,50,app->getLanguageManager()->getFromCurrentLanguage("menu_authors"),app->getResourceManager()->getFont("default",20),app->getRenderer());
	buttonExit=new GUIButton(15,450,200,50,app->getLanguageManager()->getFromCurrentLanguage("menu_exit"),app->getResourceManager()->getFont("default",20),app->getRenderer());
    std::string versionString="git-";
    #ifdef __ANDROID__
    versionString+="ANDROID(ARM)";
    #elif __linux__
    versionString+="LINUX";
    #elif _WIN32
    versionString+="WINDOWS";
    #elif __APPLE__
    versionString+="MACOSX";
    #elif unix
    versionString+="BSD";
    #endif
    versionString+=" 2021 (C) mrkubax10";
    labelVersion=new GUILabel(0,0,versionString,app->getRenderer(),app->getResourceManager()->getFont("default",10),{255,255,255});
    labelVersion->setY(app->getWindowH()-labelVersion->getH());
    app->getGUIManager()->add(imageLogo);
    app->getGUIManager()->add(buttonPlay);
    app->getGUIManager()->add(buttonFastGame);
    app->getGUIManager()->add(buttonEditor);
    app->getGUIManager()->add(buttonSettings);
    app->getGUIManager()->add(buttonAuthors);
    app->getGUIManager()->add(buttonExit);
    app->getGUIManager()->add(labelVersion);
    imageLogo->center(app->getWindowW(),app->getWindowH(),false);
    buttonPlay->center(app->getWindowW(),app->getWindowH(),false);
    buttonFastGame->center(app->getWindowW(),app->getWindowH(),false);
    buttonEditor->center(app->getWindowW(),app->getWindowH(),false);
    buttonSettings->center(app->getWindowW(),app->getWindowH(),false);
    buttonAuthors->center(app->getWindowW(),app->getWindowH(),false);
    buttonExit->center(app->getWindowW(),app->getWindowH(),false);
    buttonPlay->setCallback([](void* argument){
		((App*)argument)->setFrame(GAME_MENU_FRAME);
	},(void*)app);
	buttonEditor->setCallback([](void* argument){
		((App*)argument)->setFrame(EDITOR_MENU_FRAME);
	},(void*)app);
	buttonExit->setCallback([](void* argument){
		((App*)argument)->setRunning(false);
	},(void*)app);
    glViewport(0,0,app->getWindowW(),app->getWindowH());
    app->getRenderer()->update(app->getWindowW(),app->getWindowH());
    MenuFrame::logoFull=app->getResourceManager()->getNativeTexture("logo_full");
}
void MenuFrame::render(){
    while(SDL_PollEvent(MenuFrame::app->getEvent())){
        if(MenuFrame::app->getEvent()->type==SDL_QUIT)
            MenuFrame::app->setRunning(false);
        if(MenuFrame::app->getEvent()->type==SDL_WINDOWEVENT){
            if(app->getEvent()->window.event==SDL_WINDOWEVENT_RESIZED){
                labelVersion->setY(app->getWindowH()-labelVersion->getH()-1);
                app->getRenderer()->update(app->getWindowW(),app->getWindowH());
                glViewport(0,0,app->getWindowW(),app->getWindowH());
                imageLogo->center(app->getWindowW(),app->getWindowH(),false);
                buttonPlay->center(app->getWindowW(),app->getWindowH(),false);
                buttonFastGame->center(app->getWindowW(),app->getWindowH(),false);
                buttonEditor->center(app->getWindowW(),app->getWindowH(),false);
                buttonSettings->center(app->getWindowW(),app->getWindowH(),false);
                buttonAuthors->center(app->getWindowW(),app->getWindowH(),false);
                buttonExit->center(app->getWindowW(),app->getWindowH(),false);
            }
        }
        app->getGUIManager()->update(app->getEvent());
    }
    glClearColor(0,0,1,1);
    glClear(GL_COLOR_BUFFER_BIT);
    app->getGUIManager()->draw();
    SDL_GL_SwapWindow(app->getWindow());
}
void MenuFrame::finish(){
    delete buttonPlay;
    delete buttonFastGame;
    delete buttonEditor;
    delete buttonSettings;
    delete buttonAuthors;
    delete buttonExit;
}