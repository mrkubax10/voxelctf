#include "editormenuframe.hpp"
#include "../framework/app.hpp"
#include "frameconstants.hpp"
void EditorMenuFrame::begin(){
    Mix_FadeOutMusic(400);
    app->setTitle("VoxelCTF - Editor");
    app->getGUIManager()->clear();
    menuInfo=new GUILabel(2,2,app->getLanguageManager()->getFromCurrentLanguage("editor_devinfo"),app->getResourceManager()->getFont("default",12),{255,0,0},app->getRenderer());
	mapName=new GUITextbox(30,30,300,25,app->getResourceManager()->getFont("default",15),app->getRenderer(),"Map name");
	edit=new GUIButton(5,90,100,25,app->getLanguageManager()->getFromCurrentLanguage("editor_edit"),app->getResourceManager()->getFont("default",17),app->getRenderer());
    app->getGUIManager()->add(menuInfo);
    app->getGUIManager()->add(mapName);
    app->getGUIManager()->add(edit);
}
void EditorMenuFrame::render(){
    while(SDL_PollEvent(app->getEvent())){
        if(app->getEvent()->type==SDL_QUIT)
            app->setRunning(false);
        if(app->getEvent()->type==SDL_MOUSEBUTTONDOWN && app->getEvent()->button.button==SDL_BUTTON_LEFT){
			if(edit->isMouseOn(app->getEvent()->motion.x,app->getEvent()->motion.y)){
				app->setEditorMapName(mapName->getText());
                app->setFrame(EDITOR_FRAME);
			}
							
		}
        app->getGUIManager()->update(app->getEvent());
    }
    SDL_SetRenderDrawColor(app->getRenderer(),0,0,0,255);
    SDL_RenderClear(app->getRenderer());
    app->getGUIManager()->draw();
    SDL_RenderPresent(app->getRenderer());
}
void  EditorMenuFrame::finish(){
}