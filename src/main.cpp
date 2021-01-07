/*
 * main.cpp
 *
 *  Created on: 17 mar 2020
 *      Author: kuba
 */
#include <iostream>
#include "global.hpp"
#include "managers/resourcemanager.hpp"
#include "managers/languagemanager.hpp"
#include "SDL2_gui/SDLGui.h"
#include <GL/glew.h>
#include <GL/gl.h>
#include "world/block.hpp"
#include "world/textureatlas.hpp"
#include "gameplay/player.hpp"
#include "maths/aabb.hpp"
#include "editor/editorutils.hpp"
#include <thread>
#include "render/gl2drenderer.hpp"
#include "maths/ray.hpp"
#include "network/serverconnection.hpp"
#include "editor/gui_blockinfo.hpp"
#include "network/chat.hpp"
#include "world/skybox.hpp"
Uint32 timer1(Uint32 interval, void *param){
    SDL_Event event;
    SDL_UserEvent userevent;
    userevent.type = SDL_USEREVENT;
    userevent.code = 0;
    userevent.data1 = NULL;
    userevent.data2 = NULL;
    event.type = SDL_USEREVENT;
    event.user = userevent;
    SDL_PushEvent(&event);
    return(interval);
}
Uint32 timer2(Uint32 interval, void *param){
    SDL_Event event;
    SDL_UserEvent userevent;
    userevent.type = SDL_USEREVENT+1;
    userevent.code = 0;
    userevent.data1 = NULL;
    userevent.data2 = NULL;
    event.type = SDL_USEREVENT+1;
    event.user = userevent;
    SDL_PushEvent(&event);
    return(interval);
}

int main(int argc,char *args[]){
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	SDLNet_Init();
	Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,1024);
	bool running=true;
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 3 );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
	SDL_Window *window=SDL_CreateWindow("BlockCTF",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,1024,720,SDL_WINDOW_RESIZABLE|SDL_WINDOW_OPENGL);
	SDL_Renderer* render=SDL_CreateRenderer(window,0,0);
	SDL_GLContext contextGL=SDL_GL_CreateContext(window);
	if(contextGL==0){
		std::cout<<"(Error) [OpenGL] Failed to create OpenGL context version 3.3! Try using OSMesa compiled version of game."<<std::endl;
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,"GLContext","Failed to create OpenGL context version 3.3\nTry using OSMesa compiled version of game",0);
		running=0;
	}
	SDL_GL_MakeCurrent(window,contextGL);
	glewInit();
	
	SDL_Event event;
	GUIManager guiManager(render);
	ResourceManager resManager(render);
	LanguageManager langManager("res/translations");
	TextureAtlas textureAtlas(render);
	textureAtlas.generateTextureAtlas(&resManager);
	int frame=0;
	Settings settings;
	settings.fov=70.0f;
	int mouseX,mouseY;
	GL2DRenderer gl2dRenderer(window,render);
	int windowW,windowH;
	SDL_GetWindowSize(window,&windowW,&windowH);
	Chat chat(render,resManager.getFont("default",15));
	ServerConnection serverConnection(&chat);
	std::string editorMapName="";
	
	while(running){
		if(frame==0){
			SDL_SetWindowTitle(window,"VoxelCTF");
			guiManager.clear();
			GUILabel labelLogo(10,5,"VoxelCTF",resManager.getFont("default",80),{0,0,255},render);
			GUIButton buttonPlay(15,100,200,50,langManager.getFromCurrentLanguage("menu_play"),resManager.getFont("default",20),render);
			GUIButton buttonFastGame(15,170,200,50,langManager.getFromCurrentLanguage("menu_fastgame"),resManager.getFont("default",20),render);
			GUIButton buttonEditor(15,240,200,50,langManager.getFromCurrentLanguage("menu_editor"),resManager.getFont("default",20),render);
			GUIButton buttonSettings(15,310,200,50,langManager.getFromCurrentLanguage("menu_settings"),resManager.getFont("default",20),render);
			GUIButton buttonAuthors(15,380,200,50,langManager.getFromCurrentLanguage("menu_authors"),resManager.getFont("default",20),render);
			GUIButton buttonExit(15,450,200,50,langManager.getFromCurrentLanguage("menu_exit"),resManager.getFont("default",20),render);
			buttonPlay.setCallback([](void* argument){
				*((int*)argument)=1;
			},(void*)(&frame));
			buttonEditor.setCallback([](void* argument){
				*((int*)argument)=3;
			},(void*)&frame);
			guiManager.add(&labelLogo);
			guiManager.add(&buttonPlay);
			guiManager.add(&buttonFastGame);
			guiManager.add(&buttonEditor);
			guiManager.add(&buttonSettings);
			guiManager.add(&buttonAuthors);
			guiManager.add(&buttonExit);
			while(frame==0 && running){
				while(SDL_PollEvent(&event)){
					if(event.type==SDL_QUIT)running=0;
					if(event.type==SDL_WINDOWEVENT){
						if(event.window.event==SDL_WINDOWEVENT_RESIZED){
							
						}
					}
					
					guiManager.update(&event);
				}
				SDL_SetRenderDrawColor(render,0,0,0,255);
				SDL_RenderClear(render);
				guiManager.draw();
				SDL_RenderPresent(render);

			}
		}
		if(frame==1){
			guiManager.clear();
			GUITextbox textboxIp(10,40,200,25,resManager.getFont("default",15),render);
			GUILabel textboxIpInfo(10,10,langManager.getFromCurrentLanguage("enter_ip"),resManager.getFont("default",20),{255,255,255},render);
			GUITextbox textboxName(10,90,200,25,resManager.getFont("default",15),render);
			GUILabel textboxNameInfo(10,63,langManager.getFromCurrentLanguage("enter_name"),resManager.getFont("default",20),{255,255,255},render);
			GUIButton buttonPlay(5,400,100,25,langManager.getFromCurrentLanguage("play"),resManager.getFont("default",20),render);
			guiManager.add(&textboxIp);
			guiManager.add(&textboxIpInfo);
			guiManager.add(&textboxName);
			guiManager.add(&textboxNameInfo);
			guiManager.add(&buttonPlay);
			while(frame==1 && running){
				while(SDL_PollEvent(&event)){
					if(event.type==SDL_QUIT)running=0;
					if(event.type==SDL_MOUSEBUTTONDOWN){
						if(buttonPlay.isMouseOn(event.motion.x,event.motion.y)){
							if(serverConnection.connect(textboxIp.getText(),1255,textboxName.getText())){
								frame=2;
							}
							
						}
					}
					guiManager.update(&event);
				}
				SDL_SetRenderDrawColor(render,0,0,0,255);
				SDL_RenderClear(render);
				guiManager.draw();
				SDL_RenderPresent(render);
			}
		}
		if(frame==2){
			World world;
			serverConnection.initGame(&world,&textureAtlas);
			FPSCamera cam;
			SDL_GetWindowSize(window,&windowW,&windowH);
			cam.setProjection(glm::perspective(glm::radians(settings.fov),(float)windowW/(float)windowH,0.1f,1000.0f));
			gl2dRenderer.setTextureSize(windowW,windowH);
			Player player(&cam);
			SDL_CaptureMouse(SDL_TRUE);
			SDL_SetRelativeMouseMode(SDL_TRUE);
			SDL_TimerID activityTimer=SDL_AddTimer(1000,timer1,0);
			SDL_TimerID moveTimer=SDL_AddTimer(50,timer2,0);
			Model playerModel=createBoxModel();
			guiManager.clear();
			
			while(frame==2 && running){
				long fpsTime=SDL_GetTicks();
				const Uint8* keyboard=SDL_GetKeyboardState(0);
				while(SDL_PollEvent(&event)){
					if(event.type==SDL_QUIT)running=0;
					if(event.type==SDL_WINDOWEVENT){
						if(event.window.event==SDL_WINDOWEVENT_RESIZED){
							glViewport(0,0,event.window.data1,event.window.data2);
							cam.setProjection(glm::perspective(glm::radians(settings.fov),(float)event.window.data1/(float)event.window.data2,0.1f,1000.0f));
							gl2dRenderer.setTextureSize(event.window.data1,event.window.data2);
							windowW=event.window.data1;
							windowH=event.window.data2;
						}
					}
					if(event.type==SDL_USEREVENT){
						//serverConnection.updateActivity();
					}
					if(event.type==SDL_USEREVENT+1){
						//serverConnection.sendPosition(player.getPosition());
					}
					
				}
				glClearColor(0,0.5f,1,1);
				glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
				SDL_GetMouseState(&mouseX,&mouseY);
				player.update(keyboard,&world,settings,true);
				cam.update(mouseX,mouseY,settings);
				textureAtlas.use();
				if(keyboard[SDL_SCANCODE_F1])
					glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
				else
					glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
				world.draw(cam,resManager.getShaderProgram("world"),resManager.getShaderProgram("fluid"));
				serverConnection.drawPlayers(&playerModel,resManager.getShaderProgram("object"),cam);
				gl2dRenderer.start();
				SDL_SetRenderDrawColor(render,0,0,0,0);
				//SDL_RenderFillRect(render,0);
				//guiManager.draw();
				chat.draw(windowW,windowH);
				gl2dRenderer.finish(resManager.getShaderProgram("2dtextured"));
				SDL_GL_SwapWindow(window);
			}
			serverConnection.disconnect();
			world.destroy();
		}
		if(frame==3){
			SDL_SetWindowTitle(window,"VoxelCTF - Editor");
			guiManager.clear();
			GUILabel menuInfo(2,2,langManager.getFromCurrentLanguage("editor_devinfo"),resManager.getFont("default",12),{255,0,0},render);
			GUITextbox mapName(30,30,300,25,resManager.getFont("default",15),render,"Map name");
			GUIButton edit(5,90,100,25,langManager.getFromCurrentLanguage("editor_edit"),resManager.getFont("default",17),render);
			guiManager.add(&menuInfo);
			guiManager.add(&mapName);
			guiManager.add(&edit);
			while(frame==3 && running){
				while(SDL_PollEvent(&event)){
					if(event.type==SDL_QUIT)running=0;
					if(event.type==SDL_MOUSEBUTTONDOWN && event.button.button==SDL_BUTTON_LEFT){
						if(edit.isMouseOn(event.motion.x,event.motion.y)){
							frame=4;
							editorMapName=mapName.getText();
						}
							
					}
					guiManager.update(&event);
				}
				glClearColor(0,0,0,1);
				SDL_RenderClear(render);
				guiManager.draw();
				SDL_RenderPresent(render);
			}
		}
		if(frame==4){
			World world;
			FPSCamera cam;
			SDL_GetWindowSize(window,&windowW,&windowH);
			cam.setProjection(glm::perspective(glm::radians(settings.fov),(float)windowW/(float)windowH,0.1f,1000.0f));
			gl2dRenderer.setTextureSize(windowW,windowH);
			Player player(&cam);
			world.generateMesh(&textureAtlas);
			SDL_CaptureMouse(SDL_TRUE);
			SDL_SetRelativeMouseMode(SDL_TRUE);
			uint8_t currentBlockType=BlockType::STONE;
			Ray ray(&cam);
			world.generateMesh(&textureAtlas);
			bool pause=false;
			// Editor GUI
			guiManager.clear();
			GUIImage crossair(0,0,render,resManager.getTexture("crossair"));
			GUIBlockInfo blockInfo(2,2,resManager.getFont("default",25),render);
			GUIButton buttonReturn(0,0,100,25,langManager.getFromCurrentLanguage("editor_return"),resManager.getFont("default",15),render);
			buttonReturn.center(windowW,windowH,false);
			GUIButton buttonSave(0,30,100,25,langManager.getFromCurrentLanguage("editor_save"),resManager.getFont("default",15),render);
			buttonSave.center(windowW,windowH,false);
			GUIButton buttonSaveAndExit(0,60,100,25,langManager.getFromCurrentLanguage("editor_saveandexit"),resManager.getFont("default",15),render);
			buttonSaveAndExit.center(windowW,windowH,false);
			guiManager.add(&crossair);
			guiManager.add(&blockInfo);
			glm::vec3 fillPosition[2];
			if(fileExists("res/maps/"+editorMapName+".blockctf"))
				world.loadMap(editorMapName,&textureAtlas);
			Skybox skybox;
			while(frame==4 && running){
				const Uint8* keyboard=SDL_GetKeyboardState(0);
				while(SDL_PollEvent(&event)){
					guiManager.update(&event);
					if(event.type==SDL_QUIT)running=0;
					if(event.type==SDL_MOUSEBUTTONDOWN){
						if(event.button.button==SDL_BUTTON_RIGHT){
							if(!pause){
								glm::vec3 raypos=ray.cast(&world,player.getPosition(),false);
								world.setBlock(player.getPosition().x+raypos.x,player.getPosition().y+raypos.y,player.getPosition().z+raypos.z,(BlockType)currentBlockType);
								world.getChunk((player.getPosition().x+raypos.x)/CHUNK_SIZE_WD,(player.getPosition().z+raypos.z)/CHUNK_SIZE_WD)->generateMesh(&textureAtlas);
							}
						}
						if(event.button.button==SDL_BUTTON_LEFT){
							if(!pause){
								glm::vec3 raypos=ray.cast(&world,player.getPosition(),true);
								world.setBlock(player.getPosition().x+raypos.x,player.getPosition().y+raypos.y,player.getPosition().z+raypos.z,BlockType::AIR);
								world.getChunk((player.getPosition().x+raypos.x)/CHUNK_SIZE_WD,(player.getPosition().z+raypos.z)/CHUNK_SIZE_WD)->generateMesh(&textureAtlas);
							}
							if(pause){
								if(buttonReturn.isMouseOn(event.motion.x,event.motion.y)){
									pause=false;
									guiManager.clear();
									guiManager.add(&blockInfo);
									guiManager.add(&crossair);
									SDL_CaptureMouse(SDL_TRUE);
									SDL_SetRelativeMouseMode(SDL_TRUE);
								}
								if(buttonSave.isMouseOn(event.motion.x,event.motion.y)){
									world.saveMap(editorMapName);
								}
								if(buttonSaveAndExit.isMouseOn(event.motion.x,event.motion.y)){
									world.saveMap(editorMapName);
									frame=3;
								}
							}
						}
					}
					if(event.type==SDL_WINDOWEVENT){
						if(event.window.event==SDL_WINDOWEVENT_RESIZED){
							glViewport(0,0,event.window.data1,event.window.data2);
							cam.setProjection(glm::perspective(glm::radians(settings.fov),(float)event.window.data1/(float)event.window.data2,0.1f,1000.0f));
							gl2dRenderer.setTextureSize(event.window.data1,event.window.data2);
							buttonReturn.center(event.window.data1,event.window.data2,false);
							buttonSave.center(event.window.data1,event.window.data2,false);
							buttonSaveAndExit.center(event.window.data1,event.window.data2,false);
						}
					}
					if(event.type==SDL_MOUSEWHEEL){
						if(currentBlockType>BlockType::STONE && event.wheel.y<0){
							currentBlockType--;
						}
						if(currentBlockType<255 && event.wheel.y>0){
							currentBlockType++;
						}
					}
					if(event.type==SDL_KEYDOWN){
						if(event.key.keysym.scancode==SDL_SCANCODE_ESCAPE){
							if(pause){
								pause=false;
								guiManager.clear();
								guiManager.add(&blockInfo);
								guiManager.add(&crossair);
								SDL_CaptureMouse(SDL_TRUE);
								SDL_SetRelativeMouseMode(SDL_TRUE);
							}else{
								pause=true;
								guiManager.add(&buttonReturn);
								guiManager.add(&buttonSave);
								guiManager.add(&buttonSaveAndExit);
								SDL_CaptureMouse(SDL_FALSE);
								SDL_SetRelativeMouseMode(SDL_FALSE);
							}
						}
						if(event.key.keysym.scancode==SDL_SCANCODE_1){
							fillPosition[0]=player.getPosition();
						}
						if(event.key.keysym.scancode==SDL_SCANCODE_2){
							fillPosition[1]=player.getPosition();
							glm::vec3 tempPos;
							std::vector<glm::vec2> chunksToUpdate;
							if(fillPosition[0].x>fillPosition[1].x || fillPosition[0].y>fillPosition[1].y || fillPosition[0].z>fillPosition[1].z){
								tempPos=fillPosition[0];
								fillPosition[0]=fillPosition[1];
								fillPosition[1]=tempPos;
							}
							for(int x=fillPosition[0].x; x<fillPosition[1].x; x++){
								for(int y=fillPosition[0].y; y<fillPosition[1].y; y++){
									for(int z=fillPosition[0].z; z<fillPosition[1].z; z++){
										world.setBlock(x,y,z,(BlockType)currentBlockType);
										if(!findChunkInVector(chunksToUpdate,glm::vec2(x/CHUNK_SIZE_WD,z/CHUNK_SIZE_WD))){
											chunksToUpdate.push_back(glm::vec2(x/CHUNK_SIZE_WD,z/CHUNK_SIZE_WD));
										}
									}
								}
							}
							for(int i=0; i<chunksToUpdate.size(); i++){
								world.getChunk(chunksToUpdate[i].x,chunksToUpdate[i].y)->generateMesh(&textureAtlas);
							}
						}
					}
					
				}
				glClearColor(0,0.5f,1,1);
				glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
				SDL_GetMouseState(&mouseX,&mouseY);
				if(!pause){
					player.update(keyboard,&world,settings,!false);
					cam.update(mouseX,mouseY,settings);
				}
				
				if(keyboard[SDL_SCANCODE_F1])
					glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
				else
					glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
				skybox.draw(resManager.getShaderProgram("skybox"),cam);
				textureAtlas.use();
				world.draw(cam,resManager.getShaderProgram("world"),resManager.getShaderProgram("fluid"));
				
				gl2dRenderer.start();
				SDL_SetRenderDrawColor(render,0,0,0,0);
				SDL_RenderFillRect(render,0);
				SDL_GetWindowSize(window,&windowW,&windowH);
				crossair.center(windowW,windowH);
				guiManager.draw();
				gl2dRenderer.finish(resManager.getShaderProgram("2dtextured"));
				SDL_GL_SwapWindow(window);
			}
			world.destroy();
			//skybox.destroy();
		}
	}
	if(serverConnection.isConnected())
		serverConnection.disconnect();
	TTF_Quit();
	SDLNet_Quit();
	SDL_Quit();
	return 0;
}
