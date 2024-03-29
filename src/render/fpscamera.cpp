/*
 * fpscamera.cpp
 *
 *  Created on: 28 mar 2020
 *      Author: kuba
 */

#include "fpscamera.hpp"

FPSCamera::FPSCamera() {
	FPSCamera::firstMouse=true;
}
void FPSCamera::update(short mx,short my,Settings* settings){
	if(FPSCamera::firstMouse){
		FPSCamera::lastMousePos.x=mx;
		FPSCamera::lastMousePos.y=my;
		FPSCamera::firstMouse=false;
	}
	glm::vec2 offset=glm::vec2(0.0f,0.0f);
	offset.x=mx-lastMousePos.x;
	offset.y=lastMousePos.y-my;
	offset*=settings->sensitivity;
	if(offset.y+pitch>89){
		pitch=89;
		offset.y=0;
	}
	if(offset.y+pitch<-89){
		pitch=-89;
		offset.y=0;
	}
	if(yaw>360)
		yaw=0;
	if(yaw<0)
		yaw=360;
	FPSCamera::setRotation(offset.y+pitch,offset.x+yaw);
	
	
	lastMousePos.x=mx;
	lastMousePos.y=my;
}
