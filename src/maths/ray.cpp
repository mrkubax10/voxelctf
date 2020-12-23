/*
 * ray.cpp
 *
 *  Created on: 8 kwi 2020
 *      Author: kuba
 */

#include "ray.hpp"

Ray::Ray(FPSCamera* cam){
	Ray::cam=cam;
}


void Ray::step(){
	rayPos+=cam->getFront();
}
glm::vec3 Ray::cast(World* world,glm::vec3 offset,bool destroy){
	rayPos=glm::vec3();
	for(int i=0; i<5; i++){
		Ray::step();
		if(world->getBlock(glm::floor(offset.x+rayPos.x),glm::floor(offset.y+rayPos.y),glm::floor(offset.z+rayPos.z))->type!=BlockType::AIR){
			if(!destroy) rayPos-=cam->getFront();
			break;
		}


	}
	return rayPos;
}
