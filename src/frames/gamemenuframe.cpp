#include "gamemenuframe.hpp"
#include "../framework/app.hpp"
#include "frameconstants.hpp"
void GameMenuFrame::begin(){
    Mix_FadeOutMusic(400);
	app->getGUIManager()->clear();
    textboxIp=new GUITextbox(10,40,200,25,app->getResourceManager()->getFont("default",15),app->getRenderer());
	textboxIpInfo=new GUILabel(10,10,app->getLanguageManager()->getFromCurrentLanguage("enter_ip"),app->getResourceManager()->getFont("default",20),{255,255,255},app->getRenderer());
	textboxName=new GUITextbox(10,90,200,25,app->getResourceManager()->getFont("default",15),app->getRenderer(),app->getSettings()->lastName);
    textboxNameInfo=new GUILabel(10,63,app->getLanguageManager()->getFromCurrentLanguage("enter_name"),app->getResourceManager()->getFont("default",20),{255,255,255},app->getRenderer());
	buttonPlay=new GUIButton(5,400,100,25,app->getLanguageManager()->getFromCurrentLanguage("play"),app->getResourceManager()->getFont("default",20),app->getRenderer());
    
    app->getGUIManager()->add(textboxIp);
	app->getGUIManager()->add(textboxIpInfo);
	app->getGUIManager()->add(textboxName);
	app->getGUIManager()->add(textboxNameInfo);
	app->getGUIManager()->add(buttonPlay);
}
void GameMenuFrame::render(){
    while(SDL_PollEvent(app->getEvent())){
        if(app->getEvent()->type==SDL_QUIT)
            app->setRunning(false);
        if(app->getEvent()->type==SDL_MOUSEBUTTONDOWN){
            if(app->getEvent()->button.button==SDL_BUTTON_LEFT){
                if(buttonPlay->isMouseOn(app->getEvent()->motion.x,app->getEvent()->motion.y)){
                    if(app->getServerConnection()->connect(textboxIp->getText(),1255,textboxName->getText())){
                        app->setFrame(GAME_FRAME);
                    }
                }
            }
        }
        app->getGUIManager()->update(app->getEvent());
    }
    SDL_SetRenderDrawColor(app->getRenderer(),0,0,0,255);
    SDL_RenderClear(app->getRenderer());
    app->getGUIManager()->draw();
    SDL_RenderPresent(app->getRenderer());
}
void GameMenuFrame::finish(){
    app->getSettings()->lastName=textboxName->getText();
    delete textboxIp;
    delete textboxIpInfo;
    delete textboxName;
    delete textboxNameInfo;
    delete buttonPlay;
}
///////////////////////////////////
