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
Mix_Music* ResourceManager::getMusic(std::string name){
	if(ResourceManager::music.count(name)){
		return ResourceManager::music[name];
	}
	ResourceManager::music[name]=Mix_LoadMUS(std::string("res/music/"+name+".ogg").c_str());
	if(!ResourceManager::music[name]){
		std::cout<<"(Warn) [ResourceManager] Failed to load music "<<name<<std::endl;
		return 0;
	}
	std::cout<<"(Log) [ResourceManager] Loaded music "<<name<<std::endl;
	return ResourceManager::music[name];
}
Model* ResourceManager::getOBJModel(std::string name){
	std::fstream file;
	file.open("res/models/"+name+".obj",std::ios::in);
	
	std::string line;
	std::vector<float> vertices;
	while(getline(file,line)){
		if(line[0]=='#')
			continue;
		
	}
}
void ResourceManager::destroy(){
	std::cout<<"(Log) [ResourceManager] Destroying data"<<std::endl;
	for(std::map<std::string,ShaderProgram>::iterator i=ResourceManager::shaderprograms.begin(); i!=ResourceManager::shaderprograms.end(); i++){
		i->second.destroy();
	}
	for(std::map<std::string,SDL_Texture*>::iterator i=ResourceManager::textures.begin(); i!=ResourceManager::textures.end(); i++){
		SDL_DestroyTexture(i->second);
	}
	for(std::map<std::string,Mix_Music*>::iterator i=ResourceManager::music.begin(); i!=ResourceManager::music.end(); i++){
		Mix_FreeMusic(i->second);
	}
}