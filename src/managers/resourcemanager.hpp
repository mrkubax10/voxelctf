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
#include <map>
class ResourceManager {
	std::map<std::string,SDL_Texture*> textures;
	std::map<std::string,std::map<int,TTF_Font*>> fonts;
	std::map<std::string,ShaderProgram> shaderprograms;
	SDL_Renderer *render;
public:
	ResourceManager(SDL_Renderer *render);
	TTF_Font* getFont(std::string name,int size);
	SDL_Texture* getTexture(std::string name);
	ShaderProgram getShaderProgram(std::string name);
};

#endif /* SRC_MANAGERS_RESOURCEMANAGER_HPP_ */
