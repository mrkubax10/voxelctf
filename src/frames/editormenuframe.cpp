#include "editormenuframe.hpp"
#include "../framework/app.hpp"
#include "frameconstants.hpp"
#include <GL/glew.h>
#include <GL/gl.h>
void EditorMenuFrame::begin(){
    Mix_FadeOutMusic(400);
    app->setTitle("VoxelCTF - Editor");
    app->getGUIManager()->clear();
    menuInfo=new GUILabel(2,2,app->getLanguageManager()->getFromCurrentLanguage("editor_devinfo"),app->getRenderer(),app->getResourceManager()->getFont("default",12),{255,0,0});
	mapName=new GUITextbox(30,30,300,25,app->getRenderer(),app->getResourceManager()->getFont("default",15),"Map name");
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
        if(app->getEvent()->type==SDL_WINDOWEVENT){
            if(app->getEvent()->window.event==SDL_WINDOWEVENT_RESIZED){
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
void  EditorMenuFrame::finish(){
}