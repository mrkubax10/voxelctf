#include "gameframe.hpp"
#include "../framework/app.hpp"
#include <GL/glew.h>
#include <GL/gl.h>
#include "../utils.hpp"
void GameFrame::begin(){
    GameFrame::cam=new FPSCamera();
    GameFrame::cam->setProjection(glm::perspective(glm::radians(app->getSettings()->fov),(float)app->getWindowW()/(float)app->getWindowH(),0.1f,1000.0f));
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
        if(app->getEvent()->type==SDL_USEREVENT)
            //app->getServerConnection()->updateActivity();
        if(app->getEvent()->type==SDL_USEREVENT+1){
            // if(glm::distance(GameFrame::player->getPosition(),GameFrame::lastPosition)>0.2f){
            //      app->getServerConnection()->sendPosition(GameFrame::player->getPosition());
            //      GameFrame::lastPosition=player->getPosition();
            // }
        }
        if(app->getEvent()->type==SDL_WINDOWEVENT){
			if(app->getEvent()->window.event==SDL_WINDOWEVENT_RESIZED){
				glViewport(0,0,app->getEvent()->window.data1,app->getEvent()->window.data2);
				cam->setProjection(glm::perspective(glm::radians(app->getSettings()->fov),(float)app->getEvent()->window.data1/(float)app->getEvent()->window.data2,0.1f,1000.0f));
				app->getGL2DRenderer()->setTextureSize(app->getEvent()->window.data1,app->getEvent()->window.data2);
			}
		}
        app->getGUIManager()->update(app->getEvent());
    }
    glClearColor(0.0f,0.5f,1.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    player->update(keyboard,world,app->getSettings(),false);
    cam->update(app->getMouseX(),app->getMouseY(),app->getSettings());
    
    //std::cout<<player->getPosition().x<<" "<<player->getPosition().y<<" "<<player->getPosition().z<<std::endl;
    app->getServerConnection()->update();
    app->getTextureAtlas()->use();
    world->draw(*cam,app->getResourceManager()->getShaderProgram("world"),app->getResourceManager()->getShaderProgram("fluid"));
    //app->getServerConnection()->drawPlayers(playerModel,app->getResourceManager()->getShaderProgram("object"),*cam);
    app->getGL2DRenderer()->start();
    app->getGUIManager()->draw();
    app->getGL2DRenderer()->finish(app->getResourceManager()->getShaderProgram("2dtextured"));
    SDL_GL_SwapWindow(app->getWindow());
}
void GameFrame::finish(){
    app->getServerConnection()->disconnect();
    world->destroy();
    SDL_RemoveTimer(activityTimer);
    SDL_RemoveTimer(moveTimer);
    delete cam;
    delete player;
}