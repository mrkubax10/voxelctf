/*
 * resourcemanager.cpp
 *
 *  Created on: 17 mar 2020
 *      Author: kuba
 */

#include "resourcemanager.hpp"

ResourceManager::ResourceManager(SDL_Renderer *render) {
	ResourceManager::render=render;

}

TTF_Font* ResourceManager::getFont(std::string name,int size){
	if(ResourceManager::fonts.count(name)){
		if(ResourceManager::fonts[name].count(size)){
			return ResourceManager::fonts[name][size];
		}
	}
	ResourceManager::fonts[name][size]=TTF_OpenFont(std::string("res/fonts/"+name+".ttf").c_str(),size);
	if(!ResourceManager::fonts[name][size]){
		std::cout<<"(Warn) [ResourceManager] Failed to load font "<<name<<" with size "<<size<<std::endl;
		return 0;
	}
	std::cout<<"(Log) [ResourceManager] Loaded font "<<name<<" with size "<<size<<std::endl;
	return ResourceManager::fonts[name][size];
}
SDL_Texture* ResourceManager::getTexture(std::string name){
	if(ResourceManager::textures.count(name)){
		return ResourceManager::textures[name];
	}
	ResourceManager::textures[name]=IMG_LoadTexture(ResourceManager::render,std::string("res/textures/"+name+".png").c_str());
	if(!ResourceManager::textures[name]){
		std::cout<<"(Warn) [ResourceManager] Failed to load texture "<<name<<std::endl;
		return 0;
	}
	std::cout<<"(Log) [ResourceManager] Loaded texture "<<name<<std::endl;
	return ResourceManager::textures[name];
}
ShaderProgram ResourceManager::getShaderProgram(std::string name){
	if(ResourceManager::shaderprograms.count(name)){
		return ResourceManager::shaderprograms[name];
	}
	ResourceManager::shaderprograms[name]=ShaderProgram();
	ResourceManager::shaderprograms[name].loadFromFiles("res/shaders/"+name+"_vert.glsl","res/shaders/"+name+"_frag.glsl");

	std::cout<<"(Log) [ResourceManager] Loaded shaderprogram "<<name<<std::endl;
	return ResourceManager::shaderprograms[name];
}
