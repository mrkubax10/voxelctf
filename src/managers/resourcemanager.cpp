/*
 * resourcemanager.cpp
 *
 *  Created on: 17 mar 2020
 *      Author: kuba
 */

#include "resourcemanager.hpp"
#include <GL/glew.h>
#include <GL/gl.h>
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
Texture* ResourceManager::getNativeTexture(std::string name){
	if(ResourceManager::nativeTextures.count(name)){
		return ResourceManager::nativeTextures[name];
	}
	SDL_Surface* surf=IMG_Load(std::string("res/textures/"+name+".png").c_str());
	if(!surf){
		std::cout<<"(Warn) [ResourceManager] Failed to load native texture "<<name<<std::endl;
		return 0;
	}
	Texture* texture=new Texture();
	texture->loadFromSurface(surf);
	SDL_FreeSurface(surf);
	ResourceManager::nativeTextures[name]=texture;
	return texture;
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
	if(ResourceManager::models.count(name)){
		return ResourceManager::models[name];
	}
	std::fstream file;
	file.open("res/models/"+name+".obj",std::ios::in);
	
	std::string line;
	std::vector<float> vertices;
	std::vector<float> fileuvs;
	std::vector<float> uvs;
	std::vector<int> vertexIndices;
	std::vector<int> uvIndices;
	std::cout<<"(Log) [ResourceManager] Loaded model "<<name<<std::endl;
	while(getline(file,line)){
		if(line[0]=='#')
			continue;
		std::vector<std::string> data=split(line,' ');
		if(data[0]=="v"){
			float x=std::stof(data[1]);
			float y=std::stof(data[2]);
			float z=std::stof(data[3]);
			vertices.push_back(x);
			vertices.push_back(y);
			vertices.push_back(z);
		}
		else if(data[0]=="vt"){
			float x=std::stof(data[1]);
			float y=std::stof(data[2]);
			fileuvs.push_back(x);
			fileuvs.push_back(y);
		}
		else if(data[0]=="f"){
			vertexIndices.push_back(std::stoi(split(data[1],'/')[0])-1);
			vertexIndices.push_back(std::stoi(split(data[2],'/')[0])-1);
			vertexIndices.push_back(std::stoi(split(data[3],'/')[0])-1);
			uvIndices.push_back(std::stoi(split(data[1],'/')[1])-1);
			uvIndices.push_back(std::stoi(split(data[2],'/')[1])-1);
			uvIndices.push_back(std::stoi(split(data[3],'/')[1])-1);
		}
	}
	for(int i=0; i<uvIndices.size(); i++){
		uvs.push_back(fileuvs[uvIndices[i+1]-1]);
		uvs.push_back(fileuvs[uvIndices[i]-1]);
		
	}
	file.close();
	Model* model=new Model(vertices,uvs,vertexIndices);
	ResourceManager::models[name]=model;
	return model;
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