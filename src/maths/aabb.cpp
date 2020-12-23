/*
 * aabb.cpp
 *
 *  Created on: 28 mar 2020
 *      Author: kuba
 */

#include "aabb.hpp"
bool AABB::boxColliding(glm::vec3 a,glm::vec3 b,glm::vec3 asize,glm::vec3 bsize){
	return (a.x<=b.x+bsize.x && a.x+asize.x>=b.x && a.y<=b.y+bsize.y && a.y+asize.y>=b.y && a.z<=b.z+bsize.z && a.z+asize.z>=b.z);
}
bool AABB::sphereColliding(glm::vec4 a,glm::vec4 b){
	float dist=glm::sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)+(a.z-b.z)*(a.z-b.z));
	return (dist<a.w+b.w);
}
