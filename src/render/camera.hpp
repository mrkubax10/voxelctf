/*
 * camera.hpp
 *
 *  Created on: 19 mar 2020
 *      Author: kuba
 */

#ifndef SRC_GAMEPLAY_CAMERA_HPP_
#define SRC_GAMEPLAY_CAMERA_HPP_
#include "../global.hpp"
#include <glm/gtc/matrix_transform.hpp>
class Camera {
protected:
	glm::mat4 projection;
	glm::vec3 position;
	float pitch,yaw;
	glm::mat4 view;
	glm::vec3 cameraFront;
public:
	Camera();
	void setProjection(glm::mat4 p);
	glm::mat4 getView();
	glm::mat4 getProjection();
	void setPosition(glm::vec3 pos);
	void setRotation(float pitch,float yaw);
	glm::vec3 getPosition();
	float getPitch();
	float getYaw();
	glm::vec3 getFront();

};

#endif /* SRC_GAMEPLAY_CAMERA_HPP_ */
