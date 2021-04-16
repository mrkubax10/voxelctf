#include "editorframe.hpp"
#include "../framework/app.hpp"
#include "frameconstants.hpp"
#include <GL/glew.h>
#include <GL/gl.h>

#include "../utils.hpp"
void EditorFrame::begin(){
    EditorFrame::cam=new FPSCamera();
    EditorFrame::cam->setProjection(glm::perspective(glm::radians(app->getSettings()->fov),(float)app->getWindowW()/(float)app->getWindowH(),0.1f,1000.0f));
    EditorFrame::ray=new Ray(cam);
    EditorFrame::world=new World();
    EditorFrame::player=new Player(cam);
	EditorFrame::skybox=new Skybox();
    app->getGUIManager()->clear();
	crossair=new GUIImage(0,0,app->getRenderer(),app->getResourceManager()->getTexture("crossair"));
	blockInfo=new GUIBlockInfo(2,2,app->getResourceManager()->getFont("default",25),app->getRenderer());
	buttonReturn=new GUIButton(0,0,100,25,app->getLanguageManager()->getFromCurrentLanguage("editor_return"),app->getResourceManager()->getFont("default",15),app->getRenderer());
	buttonReturn->center(app->getWindowW(),app->getWindowH(),false);
	buttonSave=new GUIButton(0,30,100,25,app->getLanguageManager()->getFromCurrentLanguage("editor_save"),app->getResourceManager()->getFont("default",15),app->getRenderer());
	buttonSave->center(app->getWindowW(),app->getWindowH(),false);
	buttonSaveAndExit=new GUIButton(0,60,100,25,app->getLanguageManager()->getFromCurrentLanguage("editor_saveandexit"),app->getResourceManager()->getFont("default",15),app->getRenderer());
	buttonSaveAndExit->center(app->getWindowW(),app->getWindowH(),false);
	toolInfo=new GUIToolInfo(200,2,app->getRenderer(),app->getResourceManager());
	positionInfo=new GUILabel(0,0,"",app->getResourceManager()->getFont("default",15),{255,255,255},app->getRenderer());
    
    
    if(fileExists("res/maps/"+app->getEditorMapName()+".blockctf")){
		world->loadMap(app->getEditorMapName(),app->getTextureAtlas());
		world->generateMesh(app->getTextureAtlas());
		std::cout<<"(Log) [Editor] Loaded map "<<app->getEditorMapName()<<std::endl;
	}
    else{
		
	}
    EditorFrame::blockType=BlockType::STONE;
    SDL_CaptureMouse(SDL_TRUE);
	SDL_SetRelativeMouseMode(SDL_TRUE);
	EditorFrame::editorTool=new EditorBuildTool;
	EditorFrame::updateTimer=new Timer(2);
	EditorFrame::updateTimer->reset();
	
	app->getGUIManager()->add(blockInfo);
	app->getGUIManager()->add(toolInfo);
    app->getGUIManager()->add(crossair);
    app->getGUIManager()->add(positionInfo);
	app->getGUIManager()->add(buttonReturn);
	app->getGUIManager()->add(buttonSave);
	app->getGUIManager()->add(buttonSaveAndExit);
	buttonReturn->setVisible(false);
	buttonSave->setVisible(false);
	buttonSaveAndExit->setVisible(false);
}
void EditorFrame::render(){
    const Uint8* keyboard=SDL_GetKeyboardState(0);
    while(SDL_PollEvent(app->getEvent())){
        if(app->getEvent()->type==SDL_QUIT)
            app->setRunning(false);
        if(app->getEvent()->type==SDL_MOUSEBUTTONDOWN){
			if(!pause){
				editorTool->update(world,player,ray,app->getEvent()->button.button,(BlockType)blockType,app->getTextureAtlas());
			}
			if(app->getEvent()->button.button==SDL_BUTTON_LEFT){
				if(pause){
					if(buttonReturn->isMouseOn(app->getEvent()->motion.x,app->getEvent()->motion.y)){
						pause=false;
						SDL_CaptureMouse(SDL_TRUE);
						SDL_SetRelativeMouseMode(SDL_TRUE);
						buttonReturn->setVisible(false);
						buttonSave->setVisible(false);
						buttonSaveAndExit->setVisible(false);
						positionInfo->setVisible(true);
						blockInfo->setVisible(true);
						toolInfo->setVisible(true);
					}
					if(buttonSave->isMouseOn(app->getEvent()->motion.x,app->getEvent()->motion.y)){
						world->saveMap(app->getEditorMapName());
					}
					if(buttonSaveAndExit->isMouseOn(app->getEvent()->motion.x,app->getEvent()->motion.y)){
						world->saveMap(app->getEditorMapName());
						app->setFrame(EDITOR_MENU_FRAME);
					}
				}
			}
		}
		if(app->getEvent()->type==SDL_WINDOWEVENT){
			if(app->getEvent()->window.event==SDL_WINDOWEVENT_RESIZED){
				glViewport(0,0,app->getEvent()->window.data1,app->getEvent()->window.data2);
				cam->setProjection(glm::perspective(glm::radians(app->getSettings()->fov),(float)app->getEvent()->window.data1/(float)app->getEvent()->window.data2,0.1f,1000.0f));
				app->getGL2DRenderer()->setTextureSize(app->getEvent()->window.data1,app->getEvent()->window.data2);
				buttonReturn->center(app->getEvent()->window.data1,app->getEvent()->window.data2,false);
				buttonSave->center(app->getEvent()->window.data1,app->getEvent()->window.data2,false);
				buttonSaveAndExit->center(app->getEvent()->window.data1,app->getEvent()->window.data2,false);
			}
		}
		if(app->getEvent()->type==SDL_MOUSEWHEEL){
			if(blockType>BlockType::STONE && app->getEvent()->wheel.y<0){
				blockType--;
			}
			if(blockType<255 && app->getEvent()->wheel.y>0){
				blockType++;
			}
		}
		if(app->getEvent()->type==SDL_KEYDOWN){
			if(app->getEvent()->key.keysym.scancode==SDL_SCANCODE_ESCAPE){
				if(pause){
					pause=false;
					buttonReturn->setVisible(false);
					buttonSave->setVisible(false);
					buttonSaveAndExit->setVisible(false);
					positionInfo->setVisible(true);
					blockInfo->setVisible(true);
					toolInfo->setVisible(true);
					SDL_CaptureMouse(SDL_TRUE);
					SDL_SetRelativeMouseMode(SDL_TRUE);
				}else{
					pause=true;
					buttonReturn->setVisible(true);
					buttonSave->setVisible(true);
					buttonSaveAndExit->setVisible(true);
					positionInfo->setVisible(false);
					blockInfo->setVisible(false);
					toolInfo->setVisible(false);
					SDL_CaptureMouse(SDL_FALSE);
					SDL_SetRelativeMouseMode(SDL_FALSE);
				}
		    }
			if(app->getEvent()->key.keysym.scancode==SDL_SCANCODE_1){
				delete editorTool;
				editorTool=new EditorBuildTool;
			}
			if(app->getEvent()->key.keysym.scancode==SDL_SCANCODE_2){
				delete editorTool;
				editorTool=new EditorFillTool;
			}
			if(app->getEvent()->key.keysym.scancode==SDL_SCANCODE_3){
				delete editorTool;
				editorTool=new EditorEraseTool;
			}
			if(app->getEvent()->key.keysym.scancode==SDL_SCANCODE_4){
				delete editorTool;
				editorTool=new EditorTeam1FlagTool;
			}
			if(app->getEvent()->key.keysym.scancode==SDL_SCANCODE_5){
				delete editorTool;
				editorTool=new EditorTeam2FlagTool;
			}
		}
		
		app->getGUIManager()->update(app->getEvent());
    }
    glClearColor(0,0.5f,1,1);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	if(!pause && EditorFrame::updateTimer->update())
		player->update(keyboard,world,app->getSettings(),true,pause);
	if(!pause)
		cam->update(app->getMouseX(),app->getMouseY(),app->getSettings());
	//skybox->draw(app->getResourceManager()->getShaderProgram("skybox"),*cam);
    app->getTextureAtlas()->use();
	world->draw(*cam,app->getResourceManager()->getShaderProgram("world"),app->getResourceManager()->getShaderProgram("fluid"));
	app->getGL2DRenderer()->start();
	SDL_SetRenderDrawColor(app->getRenderer(),0,0,0,0);
	SDL_RenderFillRect(app->getRenderer(),0);
	positionInfo->setText("X:"+std::to_string((int)player->getPosition().x)+" Y:"+std::to_string((int)player->getPosition().y)+" Z:"+std::to_string((int)player->getPosition().z));
	positionInfo->setX(app->getWindowW()-positionInfo->getW()-2);
	positionInfo->setY(2);
	crossair->center(app->getWindowW(),app->getWindowH());
	app->getGUIManager()->draw();
	app->getGL2DRenderer()->finish(app->getResourceManager()->getShaderProgram("2dtextured"));
	SDL_GL_SwapWindow(app->getWindow());
}
void EditorFrame::finish(){
    world->destroy();
	delete ray;
	delete cam;
}
void EditorFrame::createEmptyMap(){
	for(int x=0; x<WORLD_SIZE*CHUNK_SIZE_WD; x++){
		for(int z=0; z<WORLD_SIZE*CHUNK_SIZE_WD; z++){
			EditorFrame::world->setBlock(x,0,z,BlockType::COBBLE);
		}
	}
	EditorFrame::world->generateMesh(app->getTextureAtlas());
}