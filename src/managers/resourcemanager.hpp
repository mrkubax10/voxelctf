/*
 * resourcemanager.h
 *
 *  Created on: 17 mar 2020
 *      Author: kuba
 */

#ifndef SRC_MANAGERS_RESOURCEMANAGER_HPP_
#define SRC_MANAGERS_RESOURCEMANAGER_HPP_
#include "../global.hpp"
#include "../render/shaderprogram.hpp"
#include "../render/model.hpp"
#include <fstream>
#include "../utils.hpp"
#include <map>
class ResourceManager {
	std::map<std::string,SDL_Texture*> textures;
	std::map<std::string,unsigned int> nativeTextures;
	std::map<std::string,std::map<int,TTF_Font*>> fonts;
	std::map<std::string,ShaderProgram> shaderprograms;
	std::map<std::string,Mix_Music*> music;
	std::map<std::string,Model*> models;
	SDL_Renderer *render;
public:
	ResourceManager(SDL_Renderer *render);
	TTF_Font* getFont(std::string name,int size);
	SDL_Texture* getTexture(std::string name);
	unsigned int getNativeTexture(std::string name);
	ShaderProgram getShaderProgram(std::string name);
	Mix_Music* getMusic(std::string name);
	Model* getOBJModel(std::string name);
	void destroy();
};

#endif /* SRC_MANAGERS_RESOURCEMANAGER_HPP_ */
