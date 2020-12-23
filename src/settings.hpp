/*
 * settings.hpp
 *
 *  Created on: 21 mar 2020
 *      Author: kuba
 */

#ifndef SRC_SETTINGS_HPP_
#define SRC_SETTINGS_HPP_
#include "global.hpp"
#include <fstream>
struct KeySettings{
	SDL_Scancode up,down,left,right,jump,editor_down;
	KeySettings():up(SDL_SCANCODE_W),down(SDL_SCANCODE_S),left(SDL_SCANCODE_A),right(SDL_SCANCODE_D),jump(SDL_SCANCODE_SPACE),editor_down(SDL_SCANCODE_LSHIFT){}
};
class Settings {
public:
	KeySettings keys;
	float sensitivity,fov;
	Settings();
	void save(std::string file);
	void load(std::string file);

};

#endif /* SRC_SETTINGS_HPP_ */
