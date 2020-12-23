/*
 * player.cpp
 *
 *  Created on: 19 mar 2020
 *      Author: kuba
 */

#include "player.hpp"
#include "../maths/aabb.hpp"
Player::Player(FPSCamera* cam) {
	Player::cam=cam;
	Player::cam->setPosition(glm::vec3(15*16+5,50,15*16+4));
	Player::cam->setRotation(0,0);
	Player::speed=0.02f;
	Player::jumping=false;
	Player::falling=true;
	Player::vel.y=-0.05;
	Player::mass=0.4f;
	Player::playerSize=glm::vec3(0.5,0.5,0.5);

}
void Player::update(const Uint8* keyboard,World* world,Settings settings,bool editor){

	if(!editor){

		// Normal game - enable physics
		if(keyboard[settings.keys.jump] && !Player::jumping){
			Player::vel.y=0.03;
			Player::jumping=1;
		}
		Player::falling=Player::vel.y<0;
		if(Player::jumping && Player::vel.y>-0.5)
			Player::vel.y-=world->getGravity();
		if(Player::falling && (BlockInformations::getBlockInformations(world->getBlock(Player::getPosition().x,std::floor(Player::getPosition().y),Player::getPosition().z)->type).collidable||
				BlockInformations::getBlockInformations(world->getBlock(Player::getPosition().x+Player::playerSize.x,std::floor(Player::getPosition().y-1),Player::getPosition().z)->type).collidable||
				BlockInformations::getBlockInformations(world->getBlock(Player::getPosition().x,std::floor(Player::getPosition().y-1),Player::getPosition().z+Player::playerSize.z)->type).collidable||
				BlockInformations::getBlockInformations(world->getBlock(Player::getPosition().x+Player::playerSize.x,std::floor(Player::getPosition().y-1),Player::getPosition().z+Player::playerSize.z)->type).collidable)){
			Player::vel.y=1-1;
			Player::jumping=false;
		}
		if((BlockInformations::getBlockInformations(world->getBlock(Player::getPosition().x,std::floor(Player::getPosition().y+Player::playerSize.y),Player::getPosition().z)->type).collidable||
						BlockInformations::getBlockInformations(world->getBlock(Player::getPosition().x+Player::playerSize.x,std::floor(Player::getPosition().y+Player::playerSize.y),Player::getPosition().z)->type).collidable||
						BlockInformations::getBlockInformations(world->getBlock(Player::getPosition().x,std::floor(Player::getPosition().y+Player::playerSize.y),Player::getPosition().z+Player::playerSize.z)->type).collidable||
						BlockInformations::getBlockInformations(world->getBlock(Player::getPosition().x+Player::playerSize.x,std::floor(Player::getPosition().y+Player::playerSize.y),Player::getPosition().z+Player::playerSize.z)->type).collidable)){
			Player::vel.y=-0.1;
		}
		if(keyboard[settings.keys.up]){
			Player::vel.x=(Player::speed*Player::cam->getFront()).x;
			Player::vel.z=(Player::speed*Player::cam->getFront()).z;
		}
		if(keyboard[settings.keys.right]){
			Player::vel.x=(glm::normalize(glm::cross(Player::cam->getFront(),glm::vec3(0,1,0)))*Player::speed).x;
			Player::vel.z=(glm::normalize(glm::cross(Player::cam->getFront(),glm::vec3(0,1,0)))*Player::speed).z;
		}
		if(keyboard[settings.keys.down]){
			Player::vel.x=-(Player::speed*Player::cam->getFront()).x;
			Player::vel.z=-(Player::speed*Player::cam->getFront()).z;
		}
		if(keyboard[settings.keys.left]){
			Player::vel.x=-(glm::normalize(glm::cross(Player::cam->getFront(),glm::vec3(0,1,0)))*Player::speed).x;
			Player::vel.z=-(glm::normalize(glm::cross(Player::cam->getFront(),glm::vec3(0,1,0)))*Player::speed).z;
		}

	}else{
		if(keyboard[settings.keys.up])
			Player::vel=Player::speed*Player::cam->getFront();
		if(keyboard[settings.keys.right])
			Player::vel=glm::normalize(glm::cross(Player::cam->getFront(),glm::vec3(0,1,0)))*Player::speed;
		if(keyboard[settings.keys.down])
			Player::vel=-Player::cam->getFront()*Player::speed;
		if(keyboard[settings.keys.left])
			Player::vel=-glm::normalize(glm::cross(Player::cam->getFront(),glm::vec3(0,1,0)))*Player::speed;
		Player::vel.y=0;
		if(keyboard[SDL_SCANCODE_LSHIFT])
			Player::vel.y=-Player::speed;
		if(keyboard[settings.keys.jump])
			Player::vel.y=Player::speed;
	}
	
	Player::setPosition(Player::getPosition()+Player::vel);
	if(editor) Player::vel.y=0;
	Player::vel.x=0;
	Player::vel.z=0;

}
glm::vec3 Player::getPosition(){
	return Player::cam->getPosition();
}
void Player::setPosition(glm::vec3 pos){
	Player::cam->setPosition(pos);
}
