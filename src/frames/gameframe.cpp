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
	GameFrame::positionTimer=new Timer(30);
	GameFrame::positionTimer->reset();
	GameFrame::skybox=new Skybox();
	app->getServerConnection()->initGame(world,app->getTextureAtlas());
	GameFrame::cam=new FPSCamera();
    GameFrame::cam->setProjection(glm::perspective(glm::radians(app->getSettings()->fov),(float)app->getWindowW()/(float)app->getWindowH(),0.1f,1000.0f));
	GameFrame::ray=new Ray(cam);
	GameFrame::player=new Player(cam);
	GameFrame::playerModel=createBoxModel();
	player->playerHasFlag=false;
	flagModel=app->getResourceManager()->getOBJModel("flag");
	GameFrame::pause=false;
	app->getGUIManager()->clear();
	crossair=new GUIImage(0,0,app->getRenderer(),app->getResourceManager()->getNativeTexture("crossair"));
	buttonReturn=new GUIButton(0,10,100,25,app->getLanguageManager()->getFromCurrentLanguage("in_return"),app->getResourceManager()->getFont("default",15),app->getRenderer());
	buttonExit=new GUIButton(0,40,100,25,app->getLanguageManager()->getFromCurrentLanguage("in_exit"),app->getResourceManager()->getFont("default",15),app->getRenderer());
	buttonReturn->center(app->getWindowW(),app->getWindowH(),false,true);
	buttonExit->center(app->getWindowW(),app->getWindowH(),false,true);
	hud=new HUD(app->getRenderer(),player,app->getResourceManager()->getFont("default",20),app);
	app->getGUIManager()->add(hud);
	app->getGUIManager()->add(buttonReturn);
	app->getGUIManager()->add(buttonExit);
	buttonReturn->setVisible(false);
	buttonExit->setVisible(false);
	app->getGUIManager()->add(crossair);
	app->getGUIManager()->add(app->getChat());
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
				glViewport(0,0,app->getWindowW(),app->getWindowH());
				cam->setProjection(glm::perspective(glm::radians(app->getSettings()->fov),(float)app->getWindowW()/(float)app->getWindowH(),0.1f,1000.0f));
				buttonReturn->center(app->getWindowW(),app->getWindowH(),false,true);
				buttonExit->center(app->getWindowW(),app->getWindowH(),false,true);
				app->getRenderer()->update(app->getWindowW(),app->getWindowH());
			}
		}
		if(app->getEvent()->type==SDL_KEYDOWN){
			if(app->getEvent()->key.keysym.scancode==SDL_SCANCODE_ESCAPE){
				if(!app->getChat()->isEnteringMessage()){
					GameFrame::pause=!GameFrame::pause;
					if(pause){
						buttonReturn->setVisible(true);
						buttonExit->setVisible(true);
						SDL_SetRelativeMouseMode(SDL_FALSE);
						SDL_CaptureMouse(SDL_FALSE);
					}
					else{
						buttonExit->setVisible(false);
						buttonReturn->setVisible(false);
						SDL_SetRelativeMouseMode(SDL_TRUE);
						SDL_CaptureMouse(SDL_TRUE);
					}
				}
				
			}
		}
		if(app->getEvent()->type==SDL_MOUSEBUTTONDOWN){
			if(app->getEvent()->button.button==SDL_BUTTON_LEFT){
				if(GameFrame::pause){
					if(buttonReturn->isMouseOn(app->getEvent()->motion.x,app->getEvent()->motion.y)){
						GameFrame::pause=false;
						buttonExit->setVisible(false);
						buttonReturn->setVisible(false);
						SDL_SetRelativeMouseMode(SDL_TRUE);
						SDL_CaptureMouse(SDL_TRUE);
					}
					if(buttonExit->isMouseOn(app->getEvent()->motion.x,app->getEvent()->motion.y)){
						app->setFrame(GAME_MENU_FRAME);
					}
				}
			}
		}
		app->getGUIManager()->update(app->getEvent());
    }
    glClearColor(0,0.5f,1,1);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	if(GameFrame::updateTimer->update())
		player->update(keyboard,world,app->getSettings(),false,pause||app->getChat()->isEnteringMessage());
	if(!pause && !app->getChat()->isEnteringMessage())
		cam->update(app->getMouseX(),app->getMouseY(),app->getSettings());
	if(positionTimer->update())
		app->getServerConnection()->sendPosition(player->getPosition());
	if(activityTimer->update())
		app->getServerConnection()->updateActivity();
	//skybox->draw(app->getResourceManager()->getShaderProgram("skybox"),*cam);
    app->getTextureAtlas()->use();
	world->draw(*cam,app->getResourceManager()->getShaderProgram("world"),app->getResourceManager()->getShaderProgram("fluid"));
	app->getServerConnection()->update();
	app->getChat()->updateEntries();
	for(int i=0; i<app->getServerConnection()->getPlayerList().size(); i++){
		playerModel->setScale(glm::vec3(1,1.70,1));
		glm::vec3 pos=app->getServerConnection()->getPlayerList().at(i).position;
		playerModel->translate(glm::vec3(pos.x-0.5f,pos.y-1.70f,pos.z-0.5f));
		if(app->getServerConnection()->getPlayerList().at(i).team==0)
			app->getResourceManager()->getShaderProgram("object").setVec4("color",glm::vec4(0,1,0,1));
		else if(app->getServerConnection()->getPlayerList().at(i).team==1)
			app->getResourceManager()->getShaderProgram("object").setVec4("color",glm::vec4(1,0,0,1));
		else
			app->getResourceManager()->getShaderProgram("object").setVec4("color",glm::vec4(1,0,1,1));
		
		playerModel->draw(app->getResourceManager()->getShaderProgram("object"),*cam,GL_TRIANGLES);
		
	}
	world->renderEntities(app->getResourceManager()->getShaderProgram("objecttextured"),*cam,flagModel,app);
	
	if(AABB::boxColliding(player->getPosition(),world->metadata.team1FlagPosition,glm::vec3(0.7,1.5,0.7),glm::vec3(0.1,0.7,0.1)) && app->getServerConnection()->getTeam()==1 && !player->playerHasFlag){
		app->getServerConnection()->sendFlagFetch(0);
		player->playerHasFlag=true;
		app->getServerConnection()->flag1Fetch=true;
	}
	if(AABB::boxColliding(player->getPosition(),world->metadata.team2FlagPosition,glm::vec3(0.7,1.5,0.7),glm::vec3(0.1,0.7,0.1)) && app->getServerConnection()->getTeam()==0 && !player->playerHasFlag){
		app->getServerConnection()->sendFlagFetch(1);
		player->playerHasFlag=true;
		app->getServerConnection()->flag2Fetch=true;
	}
	if(AABB::boxColliding(player->getPosition(),world->metadata.team1FlagPosition,glm::vec3(0.7,1.5,0.7),glm::vec3(0.1,0.7,0.1)) && app->getServerConnection()->getTeam()==0 && player->playerHasFlag){
		app->getServerConnection()->flag2Fetch=false;
		app->getServerConnection()->sendFlagCapture(1);
		player->playerHasFlag=false;
	}
	if(AABB::boxColliding(player->getPosition(),world->metadata.team2FlagPosition,glm::vec3(0.7,1.5,0.7),glm::vec3(0.1,0.7,0.1)) && app->getServerConnection()->getTeam()==1 && player->playerHasFlag){
		app->getServerConnection()->flag1Fetch=false;
		app->getServerConnection()->sendFlagCapture(0);
		player->playerHasFlag=false;
	}
	crossair->center(app->getWindowW(),app->getWindowH());
	app->getGUIManager()->draw();
	SDL_GL_SwapWindow(app->getWindow());
}
void GameFrame::finish(){
    world->destroy();
	skybox->destroy();
	app->getServerConnection()->disconnect();
	SDL_GL_SwapWindow(app->getWindow());
	SDL_CaptureMouse(SDL_FALSE);
	SDL_SetRelativeMouseMode(SDL_FALSE);
}