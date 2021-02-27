/*
 * camera.cpp
 *
 *  Created on: 19 mar 2020
 *      Author: kuba
 */

#include "camera.hpp"

Camera::Camera() {
	Camera::projection=glm::mat4(1);
	Camera::view=glm::mat4(1);
	Camera::position=glm::vec3(0,0,0);
	Camera::pitch=0;
	Camera::yaw=0;

}
glm::mat4 Camera::getProjection(){
	return Camera::projection;
}
glm::mat4 Camera::getView(){
	return Camera::view;
}
void Camera::setPosition(glm::vec3 pos){
	Camera::position=pos;
	Camera::view=glm::mat4(1);
	glm::vec3 direction;
	direction.x=std::cos(glm::radians(yaw))*std::cos(glm::radians(pitch));
	direction.y=std::sin(glm::radians(pitch));
	direction.z=std::sin(glm::radians(yaw))*std::cos(glm::radians(pitch));
	direction=glm::normalize(direction);
	Camera::cameraFront=direction;
	Camera::view=glm::lookAt(Camera::position,Camera::position+cameraFront,glm::vec3(0,1,0));
}
void Camera::setRotation(float pitch,float yaw){
	Camera::pitch=pitch;
	Camera::yaw=yaw;
	Camera::view=glm::mat4(1);
	glm::vec3 direction;
	direction.x=std::cos(glm::radians(yaw))*std::cos(glm::radians(pitch));
	direction.y=std::sin(glm::radians(pitch));
	direction.z=std::sin(glm::radians(yaw))*std::cos(glm::radians(pitch));
	
	direction=glm::normalize(direction);
	Camera::cameraFront=direction;
	Camera::view=glm::lookAt(Camera::position,Camera::position+cameraFront,glm::vec3(0,1,0));
	
}
glm::vec3 Camera::getFront(){
	return Camera::cameraFront;
}
void Camera::setProjection(glm::mat4 p){
	Camera::projection=p;
}
float Camera::getPitch(){
	return pitch;
}
float Camera::getYaw(){
	return yaw;
}
glm::vec3 Camera::getPosition(){
	return position;
}
