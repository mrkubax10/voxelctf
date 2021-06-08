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
#include "../render/texture.hpp"
#include <map>
class App;
class ResourceManager {
	std::map<std::string,Texture*> nativeTextures;
	std::map<std::string,std::map<int,TTF_Font*>> fonts;
	std::map<std::string,ShaderProgram> shaderprograms;
	std::map<std::string,Mix_Music*> music;
	std::map<std::string,Model*> models;
	std::map<std::string,SDL_Surface*> surfaces;
	Texture* dummyTexture;
	App* app;
public:
	ResourceManager(App* app);
	TTF_Font* getFont(std::string name,int size);
	Texture* getNativeTexture(std::string name);
	ShaderProgram getShaderProgram(std::string name);
	Mix_Music* getMusic(std::string name);
	Model* getOBJModel(std::string name);
	SDL_Surface* getSurface(std::string name);
	void destroy();
	Texture* createDummyTexture();
};

#endif /* SRC_MANAGERS_RESOURCEMANAGER_HPP_ */
