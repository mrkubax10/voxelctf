/*
 * player.hpp
 *
 *  Created on: 19 mar 2020
 *      Author: kuba
 */

#ifndef SRC_GAMEPLAY_PLAYER_HPP_
#define SRC_GAMEPLAY_PLAYER_HPP_
#include "../render/fpscamera.hpp"
#include "../world/world.hpp"
#include "../settings.hpp"
class Player {
	FPSCamera* cam;
	glm::vec3 vel;
	float speed;
	bool jumping;
	bool falling;
	float mass;
	glm::vec3 playerSize;
	uint8_t hp,maxHP;
public:
	
	Player(FPSCamera* cam);
	void update(const Uint8* keyboard,World* world,Settings* settings,bool editor,bool pause);
	glm::vec3 getPosition();
	void setPosition(glm::vec3 pos);
	void setHP(uint8_t hp);
	uint8_t getHP();
	void setMaxHP(uint8_t maxhp);
	uint8_t getMaxHP();
	bool playerHasFlag;
};

#endif /* SRC_GAMEPLAY_PLAYER_HPP_ */
