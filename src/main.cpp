/*
 * main.cpp
 *
 *  Created on: 17 mar 2020
 *      Author: kuba
 */
#include "framework/app.hpp"
#include "frames/frameconstants.hpp"
#include "global.hpp"
int main(int argc,char *args[]){
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,1024)<0){
		std::cout<<"(Err) [SDL2_mixer] Failed to initialize: "<<Mix_GetError()<<std::endl;
		return 0;
	};
	if(enet_initialize()!=0){
		std::cout<<"(Err) [ENet] Failed to initialize ENet"<<std::endl;
		return 0;
	}
	MENU_FRAME=new MenuFrame();
	GAME_MENU_FRAME=new GameMenuFrame();
	GAME_FRAME=new GameFrame();
	EDITOR_MENU_FRAME=new EditorMenuFrame();
	EDITOR_FRAME=new EditorFrame();
	App* app=new App("VoxelCTF",1024,720,SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);
	//app.getSettings()->load("settings.txt");
	app->setFrame(MENU_FRAME);
	app->loop();
	app->getSettings()->save("settings.txt");
	app->destroy();
	TTF_Quit();
	Mix_Quit();
	SDL_Quit();
	std::cout<<"(Log) [Main] Exiting"<<std::endl;
	return 0;
}
