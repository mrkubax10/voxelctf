#include "gameframe.hpp"
#include "../framework/app.hpp"
#include "frameconstants.hpp"
#include <GL/glew.h>
#include <GL/gl.h>

#include "../utils.hpp"
void GameFrame::begin(){
    GameFrame::world=new World();
    SDL_CaptureMouse(SDL_TRUE);
	SDL_SetRelativeMouseMode(SDL_TRUE);
	GameFrame::updateTimer=new Timer(2);
	GameFrame::updateTimer->reset();
	GameFrame::activityTimer=new Timer(10);
	GameFrame::activityTimer->reset();
	GameFrame::positionTimer=new Timer(1);
	GameFrame::positionTimer->reset();
	GameFrame::skybox=new Skybox();
	app->getServerConnection()->initGame(world,app->getTextureAtlas());
	GameFrame::cam=new FPSCamera();
    GameFrame::cam->setProjection(glm::perspective(glm::radians(app->getSettings()->fov),(float)app->getWindowW()/(float)app->getWindowH(),0.1f,1000.0f));
	GameFrame::ray=new Ray(cam);
	GameFrame::player=new Player(cam);
	app->getGUIManager()->clear();
	crossair=new GUIImage(0,0,app->getRenderer(),app->getResourceManager()->getTexture("crossair"));
	app->getGUIManager()->add(crossair);
	app->getGUIManager()->add(app->getChat());
	app->getChat()->addEntry("Test");
	app->getChat()->addEntry("Test1");
	app->getGL2DRenderer()->setTextureSize(app->getWindowW(),app->getWindowH());
	glViewport(0,0,app->getWindowW(),app->getWindowH());
	cam->setProjection(glm::perspective(glm::radians(app->getSettings()->fov),(float)app->getWindowW()/(float)app->getWindowH(),0.1f,1000.0f));
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
	if(!pause && GameFrame::updateTimer->update() && !app->getChat()->isEnteringMessage())
		player->update(keyboard,world,app->getSettings(),false);
	if(!pause && !app->getChat()->isEnteringMessage())
		cam->update(app->getMouseX(),app->getMouseY(),app->getSettings());
	if(positionTimer->update())
		app->getServerConnection()->sendPosition(player->getPosition());
	//skybox->draw(app->getResourceManager()->getShaderProgram("skybox"),*cam);
    app->getTextureAtlas()->use();
	world->draw(*cam,app->getResourceManager()->getShaderProgram("world"),app->getResourceManager()->getShaderProgram("fluid"));
	app->getServerConnection()->update();
	app->getChat()->updateEntries();
	app->getGL2DRenderer()->start();
	SDL_SetRenderDrawColor(app->getRenderer(),0,0,0,0);
	SDL_RenderFillRect(app->getRenderer(),0);
	crossair->center(app->getWindowW(),app->getWindowH());
	app->getGUIManager()->draw();
	app->getGL2DRenderer()->finish(app->getResourceManager()->getShaderProgram("2dtextured"));
	SDL_GL_SwapWindow(app->getWindow());
}
void GameFrame::finish(){
    world->destroy();
	app->getServerConnection()->disconnect();
}