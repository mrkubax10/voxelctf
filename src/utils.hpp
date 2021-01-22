/*
 * utils.h
 *
 *  Created on: 13 sty 2020
 *      Author: jacek
 */

#ifndef SRC_UTILS_HPP_
#define SRC_UTILS_HPP_
#include "global.hpp"
#include <sstream>
#include "render/model.hpp"
void renderDraw(SDL_Renderer *render,SDL_Texture *tex,int x,int y);
void renderDrawScaled(SDL_Renderer *render,SDL_Texture *tex,int x,int y,int w,int h);
std::vector<std::string> split(std::string str,char ch);
std::string stringToLower(std::string str);
bool fileExists(std::string name);
Model* createBoxModel();
Uint32 timer(Uint32 interval,void* argument);
#endif /* SRC_UTILS_HPP_ */
