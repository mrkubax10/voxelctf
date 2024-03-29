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
	SDL_Scancode up,down,left,right,jump,editor_down,chat,scoreboard;
	KeySettings():up(SDL_SCANCODE_W),down(SDL_SCANCODE_S),left(SDL_SCANCODE_A),right(SDL_SCANCODE_D),jump(SDL_SCANCODE_SPACE),editor_down(SDL_SCANCODE_LSHIFT),chat(SDL_SCANCODE_T),scoreboard(SDL_SCANCODE_TAB){}
};
class Settings {
public:
	KeySettings keys;
	float sensitivity,fov;
	std::string lastName;
	Settings();
	void save(std::string file);
	void load(std::string file);

};

#endif /* SRC_SETTINGS_HPP_ */
