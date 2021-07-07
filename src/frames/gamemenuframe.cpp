#include "gamemenuframe.hpp"
#include "../framework/app.hpp"
#include "frameconstants.hpp"
#include <GL/glew.h>
#include <GL/gl.h>
void GameMenuFrame::begin(){
    Mix_FadeOutMusic(400);
	app->getGUIManager()->clear();
    textboxIp=new GUITextbox(10,40,200,25,app->getRenderer(),app->getResourceManager()->getFont("default",15));
	textboxIpInfo=new GUILabel(10,10,app->getLanguageManager()->getFromCurrentLanguage("enter_ip"),app->getRenderer(),app->getResourceManager()->getFont("default",20),{255,255,255});
	textboxName=new GUITextbox(10,90,200,25,app->getRenderer(),app->getResourceManager()->getFont("default",15),app->getSettings()->lastName);
    textboxNameInfo=new GUILabel(10,63,app->getLanguageManager()->getFromCurrentLanguage("enter_name"),app->getRenderer(),app->getResourceManager()->getFont("default",20),{255,255,255});
	buttonPlay=new GUIButton(10,140,100,25,app->getLanguageManager()->getFromCurrentLanguage("play"),app->getResourceManager()->getFont("default",20),app->getRenderer());
    serverlist=new GUIServerlist(app->getWindowW()-310,10,300,app->getWindowH()-20,app->getResourceManager()->getFont("default",15),app->getLanguageManager(),app->getRenderer(),textboxIp);
    textboxServerNameInfo=new GUILabel(10,200,app->getLanguageManager()->getFromCurrentLanguage("gamemenu_addserverinfo"),app->getRenderer(),app->getResourceManager()->getFont("default",20),{255,255,255});
    textboxServerName=new GUITextbox(10,205+textboxServerNameInfo->getH(),200,25,app->getRenderer(),app->getResourceManager()->getFont("default",15));
    buttonAddServer=new GUIButton(10,240+textboxServerNameInfo->getH(),100,25,app->getLanguageManager()->getFromCurrentLanguage("gamemenu_addserver"),app->getResourceManager()->getFont("default",15),app->getRenderer());
    buttonBack=new GUIButton(5,app->getWindowH()-30,100,25,app->getLanguageManager()->getFromCurrentLanguage("gamemenu_back"),app->getResourceManager()->getFont("default",15),app->getRenderer());
    app->getGUIManager()->add(textboxIp);
	app->getGUIManager()->add(textboxIpInfo);
	app->getGUIManager()->add(textboxName);
	app->getGUIManager()->add(textboxNameInfo);
	app->getGUIManager()->add(buttonPlay);
    app->getGUIManager()->add(serverlist);
    app->getGUIManager()->add(textboxServerNameInfo);
    app->getGUIManager()->add(textboxServerName);
    app->getGUIManager()->add(buttonAddServer);
    app->getGUIManager()->add(buttonBack);
    buttonPlay->setCallback([&](void* argument){
        if(textboxName->getText()!="" && textboxIp->getText()!=""){
            if(app->getServerConnection()->connect(textboxIp->getText(),1255,textboxName->getText())){
                app->setUsername(textboxName->getText());
                app->setFrame(GAME_FRAME);
            }
        }
    },0);
    buttonAddServer->setCallback([&](void* argument){
        serverlist->addServer(textboxServerName->getText(),textboxIp->getText());
        textboxServerName->setText("");
    },0);
    buttonBack->setCallback([&](void* argument){
        app->setFrame(MENU_FRAME);
    },0);
}
void GameMenuFrame::render(){
    while(SDL_PollEvent(app->getEvent())){
        if(app->getEvent()->type==SDL_QUIT)
            app->setRunning(false);
        if(app->getEvent()->type==SDL_WINDOWEVENT){
            if(app->getEvent()->window.event==SDL_WINDOWEVENT_RESIZED){
                serverlist->setX(app->getWindowW()-310);
                serverlist->setH(app->getWindowH()-20);
                buttonBack->setY(app->getWindowH()-30);
                app->getRenderer()->update(app->getWindowW(),app->getWindowH());
                glViewport(0,0,app->getWindowW(),app->getWindowH());
            }
            
        }
        app->getGUIManager()->update(app->getEvent());
    }
    glClearColor(0,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT);
    app->getGUIManager()->draw();
    SDL_GL_SwapWindow(app->getWindow());
}
void GameMenuFrame::finish(){
    //app->getSettings()->lastName=textboxName->getText();
    serverlist->saveListToFile();
    delete textboxIp;
    delete textboxIpInfo;
    delete textboxName;
    delete textboxNameInfo;
    delete buttonPlay;
}
///////////////////////////////////
