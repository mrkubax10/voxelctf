/*
 * main.cpp
 *
 *  Created on: 17 mar 2020
 *      Author: kuba
 */
#include "framework/app.hpp"
#include "frames/frameconstants.hpp"
int main(int argc,char *args[]){
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	SDLNet_Init();
	if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,1024)<0){
		std::cout<<"(Err) [SDL2_mixer] Failed to initialize: "<<Mix_GetError()<<std::endl;
		return 0;
	};
	App app("VoxelCTF",1024,720,SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);
	
	app.getSettings()->fov=70.0f;
	
	app.setFrame(MENU_FRAME);
	
	app.loop();
	if(app.getServerConnection()->isConnected())
		app.getServerConnection()->disconnect();
	SDLNet_Quit();
	SDL_Quit();
	return 0;
}
