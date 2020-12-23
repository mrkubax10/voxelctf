/*
 * ray.hpp
 *
 *  Created on: 8 kwi 2020
 *      Author: kuba
 */

#ifndef SRC_RAY_HPP_
#define SRC_RAY_HPP_
#include <glm/glm.hpp>
#include "../render/fpscamera.hpp"
#include "../world/world.hpp"
class Ray {
	glm::vec3 stepValue,rayPos;
	FPSCamera* cam;
public:
	Ray(FPSCamera* cam);
	void step();
	glm::vec3 cast(World* world,glm::vec3 offset,bool destroy);
};

#endif /* SRC_RAY_HPP_ */
