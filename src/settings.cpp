/*
 * settings.cpp
 *
 *  Created on: 21 mar 2020
 *      Author: kuba
 */

#include "settings.hpp"
#include "utils.hpp"

Settings::Settings() {
	Settings::fov=70.0f;
	Settings::sensitivity=0.2f;
	Settings::keys=KeySettings();
}
void Settings::save(std::string file){
	std::fstream fileHandle;
	fileHandle.open(file,std::ios::out);
	fileHandle<<"fov="<<fov<<std::endl;
	fileHandle<<"sensitivity="<<sensitivity<<std::endl;
	fileHandle<<"keys_up="<<keys.up<<std::endl;
	fileHandle<<"keys_down="<<keys.down<<std::endl;
	fileHandle<<"keys_left="<<keys.left<<std::endl;
	fileHandle<<"keys_right="<<keys.right<<std::endl;
	fileHandle<<"keys_jump="<<keys.jump<<std::endl;
	fileHandle.close();
}
void Settings::load(std::string file){
	std::fstream fileHandle;
	fileHandle.open(file,std::ios::in);
	std::string line;
	while(getline(fileHandle,line)){
		std::string id=split(line,'=')[0];
		float value=atof(split(line,'=')[1].c_str());
		if(id=="fov")
			fov=value;
		if(id=="sensitivity")
			sensitivity=value;
		if(id=="keys_up")
			keys.up=(SDL_Scancode)value;
		if(id=="keys_down")
			keys.down=(SDL_Scancode)value;
		if(id=="keys_left")
			keys.left=(SDL_Scancode)value;
		if(id=="keys_right")
			keys.right=(SDL_Scancode)value;
		if(id=="keys_jump")
			keys.jump=(SDL_Scancode)value;
	}
}

