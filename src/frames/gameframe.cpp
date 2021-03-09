#include "gameframe.hpp"
#include "../framework/app.hpp"
#include "frameconstants.hpp"
#include <GL/glew.h>
#include <GL/gl.h>

#include "../utils.hpp"
void GameFrame::begin(){
    GameFrame::cam=new FPSCamera();
    GameFrame::cam->setProjection(glm::perspective(glm::radians(70.0f),(float)app->getWindowW()/(float)app->getWindowH(),0.1f,1000.0f));
    GameFrame::world=new World();
    GameFrame::player=new Player(cam);
    app->getServerConnection()->initGame(world,app->getTextureAtlas());
    app->getGUIManager()->clear();
    SDL_CaptureMouse(SDL_TRUE);
	SDL_SetRelativeMouseMode(SDL_TRUE);
}
void GameFrame::render(){
    const Uint8* keyboard=SDL_GetKeyboardState(0);
    while(SDL_PollEvent(app->getEvent())){
        if(app->getEvent()->type==SDL_QUIT)
            app->setRunning(false);
		if(app->getEvent()->type==SDL_WINDOWEVENT){
			if(app->getEvent()->window.event==SDL_WINDOWEVENT_RESIZED){
				glViewport(0,0,app->getEvent()->window.data1,app->getEvent()->window.data2);
				cam->setProjection(glm::perspective(glm::radians(app->getSettings()->fov),(float)app->getEvent()->window.data1/(float)app->getEvent()->window.data2,0.1f,1000.0f));
				app->getGL2DRenderer()->setTextureSize(app->getEvent()->window.data1,app->getEvent()->window.data2);
			}
		}
		app->getGUIManager()->update(app->getEvent());
    }
    glClearColor(0,0.5f,1,1);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    player->update(keyboard,world,app->getSettings(),false);
	cam->update(app->getMouseX(),app->getMouseY(),app->getSettings());
    app->getTextureAtlas()->use();
	world->draw(*cam,app->getResourceManager()->getShaderProgram("world"),app->getResourceManager()->getShaderProgram("fluid"));
	app->getGL2DRenderer()->start();
	SDL_SetRenderDrawColor(app->getRenderer(),0,0,0,0);
	SDL_RenderFillRect(app->getRenderer(),0);
	app->getGUIManager()->draw();
	app->getGL2DRenderer()->finish(app->getResourceManager()->getShaderProgram("2dtextured"));
	SDL_GL_SwapWindow(app->getWindow());
}
void GameFrame::finish(){
    world->destroy();
	delete cam;
}