/*
 * fpscamera.h
 *
 *  Created on: 28 mar 2020
 *      Author: kuba
 */

#ifndef SRC_RENDER_FPSCAMERA_HPP_
#define SRC_RENDER_FPSCAMERA_HPP_
#include "camera.hpp"
#include "../settings.hpp"
class FPSCamera : public Camera {
	glm::vec2 lastMousePos;
	bool firstMouse;
public:
	FPSCamera();
	void update(short mx,short my,Settings* settings);

};

#endif /* SRC_RENDER_FPSCAMERA_HPP_ */
