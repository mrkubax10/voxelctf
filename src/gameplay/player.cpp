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
	Player::vel=glm::vec3(0,0,0);
	Player::setPosition(glm::vec3(128,20,128));
	Player::speed=0.02f;
	Player::jumping=false;
	Player::falling=true;
	Player::vel.y=-0.05;
	Player::mass=0.4f;
	Player::playerSize=glm::vec3(0.5,0.5,0.5);
}
void Player::update(const Uint8* keyboard,World* world,Settings* settings,bool editor,bool pause){
	glm::vec3 dir=glm::vec3(0,0,0);
	dir.x=std::cos(glm::radians(cam->getYaw()));
	dir.y=1;
	dir.z=std::sin(glm::radians(cam->getYaw()));
	if(!editor){
		if(!pause){
			if(keyboard[settings->keys.up]){
				Player::vel.x=(Player::speed*dir).x;
				Player::vel.z=(Player::speed*dir).z;
			}
			if(keyboard[settings->keys.right]){
				Player::vel.x=(glm::normalize(glm::cross(Player::cam->getFront(),glm::vec3(0,1,0)))*Player::speed).x;
				Player::vel.z=(glm::normalize(glm::cross(Player::cam->getFront(),glm::vec3(0,1,0)))*Player::speed).z;
			}
			if(keyboard[settings->keys.down]){
				Player::vel.x=-(Player::speed*dir).x;
				Player::vel.z=-(Player::speed*dir).z;
			}
			if(keyboard[settings->keys.left]){
				Player::vel.x=-(glm::normalize(glm::cross(Player::cam->getFront(),glm::vec3(0,1,0)))*Player::speed).x;
				Player::vel.z=-(glm::normalize(glm::cross(Player::cam->getFront(),glm::vec3(0,1,0)))*Player::speed).z;
			}
			if(keyboard[settings->keys.jump] && !Player::falling && !Player::jumping){
				Player::vel.y=0.03f;
				Player::jumping=true;
			}
		}
		glm::vec3 newPosition=glm::vec3(Player::getPosition().x+Player::vel.x,Player::getPosition().y+Player::vel.y,Player::getPosition().z+Player::vel.z);
		if(Player::vel.x<0){
			if(!BlockInformations::getBlockInformations(world->getBlock(newPosition.x-0.4f,Player::getPosition().y,Player::getPosition().z-0.4f)->type).collidable &&
				!BlockInformations::getBlockInformations(world->getBlock(newPosition.x-0.4f,Player::getPosition().y-1,Player::getPosition().z-0.4f)->type).collidable &&
				!BlockInformations::getBlockInformations(world->getBlock(newPosition.x-0.4f,Player::getPosition().y,Player::getPosition().z+0.4f)->type).collidable &&
				!BlockInformations::getBlockInformations(world->getBlock(newPosition.x-0.4f,Player::getPosition().y-1,Player::getPosition().z+0.4f)->type).collidable){
				Player::setPosition(glm::vec3(newPosition.x,Player::getPosition().y,Player::getPosition().z));
			}
		}
		if(Player::vel.x>0){
			if(!BlockInformations::getBlockInformations(world->getBlock(newPosition.x+0.4f,Player::getPosition().y,Player::getPosition().z-0.4f)->type).collidable &&
				!BlockInformations::getBlockInformations(world->getBlock(newPosition.x+0.4f,Player::getPosition().y-1,Player::getPosition().z-0.4f)->type).collidable &&
				!BlockInformations::getBlockInformations(world->getBlock(newPosition.x+0.4f,Player::getPosition().y,Player::getPosition().z+0.4f)->type).collidable &&
				!BlockInformations::getBlockInformations(world->getBlock(newPosition.x+0.4f,Player::getPosition().y-1,Player::getPosition().z+0.4f)->type).collidable){
				Player::setPosition(glm::vec3(newPosition.x,Player::getPosition().y,Player::getPosition().z));
			}
		}
		if(Player::vel.z<0){
			if(!BlockInformations::getBlockInformations(world->getBlock(Player::getPosition().x-0.4f,Player::getPosition().y-1,newPosition.z-0.4f)->type).collidable &&
				!BlockInformations::getBlockInformations(world->getBlock(Player::getPosition().x-0.4f,Player::getPosition().y,newPosition.z-0.4f)->type).collidable &&
				!BlockInformations::getBlockInformations(world->getBlock(Player::getPosition().x+0.4f,Player::getPosition().y-1,newPosition.z-0.4f)->type).collidable &&
				!BlockInformations::getBlockInformations(world->getBlock(Player::getPosition().x+0.4f,Player::getPosition().y-1,newPosition.z-0.4f)->type).collidable){
				Player::setPosition(glm::vec3(Player::getPosition().x,Player::getPosition().y,newPosition.z));
			}
		}
		if(Player::vel.z>0){
			if(!BlockInformations::getBlockInformations(world->getBlock(Player::getPosition().x-0.4f,Player::getPosition().y-1,newPosition.z+0.4f)->type).collidable &&
				!BlockInformations::getBlockInformations(world->getBlock(Player::getPosition().x-0.4f,Player::getPosition().y,newPosition.z+0.4f)->type).collidable &&
				!BlockInformations::getBlockInformations(world->getBlock(Player::getPosition().x+0.4f,Player::getPosition().y-1,newPosition.z+0.4f)->type).collidable &&
				!BlockInformations::getBlockInformations(world->getBlock(Player::getPosition().x+0.4f,Player::getPosition().y-1,newPosition.z+0.4f)->type).collidable){
				Player::setPosition(glm::vec3(Player::getPosition().x,Player::getPosition().y,newPosition.z));
			}
		}
		if(Player::vel.y<0){
			if(BlockInformations::getBlockInformations(world->getBlock(Player::getPosition().x-0.4f,newPosition.y-1.5f,Player::getPosition().z-0.4f)->type).collidable ||
				BlockInformations::getBlockInformations(world->getBlock(Player::getPosition().x-0.4f,newPosition.y-1.5f,Player::getPosition().z-0.4f)->type).collidable ||
				BlockInformations::getBlockInformations(world->getBlock(Player::getPosition().x+0.4f,newPosition.y-1.5f,Player::getPosition().z+0.4f)->type).collidable ||
				BlockInformations::getBlockInformations(world->getBlock(Player::getPosition().x+0.4f,newPosition.y-1.5f,Player::getPosition().z+0.4f)->type).collidable){
					Player::falling=false;
					Player::jumping=false;
			}
		}
		if(Player::vel.y>0){
			if(BlockInformations::getBlockInformations(world->getBlock(Player::getPosition().x-0.4f,newPosition.y,Player::getPosition().z-0.4f)->type).collidable ||
				BlockInformations::getBlockInformations(world->getBlock(Player::getPosition().x-0.4f,newPosition.y,Player::getPosition().z-0.4f)->type).collidable ||
				BlockInformations::getBlockInformations(world->getBlock(Player::getPosition().x+0.4f,newPosition.y,Player::getPosition().z+0.4f)->type).collidable ||
				BlockInformations::getBlockInformations(world->getBlock(Player::getPosition().x+0.4f,newPosition.y,Player::getPosition().z+0.4f)->type).collidable){
					Player::falling=true;
					Player::vel.y=-Player::vel.y;
			}
		}
		if(!BlockInformations::getBlockInformations(world->getBlock(Player::getPosition().x,newPosition.y-1.5f,Player::getPosition().z)->type).collidable &&
				!BlockInformations::getBlockInformations(world->getBlock(Player::getPosition().x,newPosition.y-1.5f,Player::getPosition().z)->type).collidable &&
				!BlockInformations::getBlockInformations(world->getBlock(Player::getPosition().x+0.4f,newPosition.y-1.5f,Player::getPosition().z+0.4f)->type).collidable &&
				!BlockInformations::getBlockInformations(world->getBlock(Player::getPosition().x+0.4f,newPosition.y-1.5f,Player::getPosition().z+0.4f)->type).collidable){
				Player::falling=true;
		}
		if(Player::falling && Player::vel.y>-0.1f) Player::vel.y-=0.0002f;
		if(!Player::falling) Player::vel.y=0;
		if(Player::vel.y==0) Player::jumping=false;
		Player::vel.x=0;
		Player::vel.z=0;
	}else{
		if(keyboard[settings->keys.up])
			Player::vel=Player::speed*dir;
		if(keyboard[settings->keys.right])
			Player::vel=glm::normalize(glm::cross(Player::cam->getFront(),glm::vec3(0,1,0)))*Player::speed;
		if(keyboard[settings->keys.down])
			Player::vel=-dir*Player::speed;
		if(keyboard[settings->keys.left])
			Player::vel=-glm::normalize(glm::cross(Player::cam->getFront(),glm::vec3(0,1,0)))*Player::speed;
		Player::vel.y=0;
		if(keyboard[SDL_SCANCODE_LSHIFT])
			Player::vel.y=-Player::speed;
		if(keyboard[settings->keys.jump])
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
