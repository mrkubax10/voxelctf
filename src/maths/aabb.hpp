/*
 * aabb.hpp
 *
 *  Created on: 28 mar 2020
 *      Author: kuba
 */

#ifndef SRC_MATHS_AABB_HPP_
#define SRC_MATHS_AABB_HPP_
#include <glm/glm.hpp>
namespace AABB{
	bool boxColliding(glm::vec3 pos1,glm::vec3 pos2,glm::vec3 asize,glm::vec3 bsize);
	bool sphereColliding(glm::vec4 a,glm::vec4 b);
}

#endif /* SRC_MATHS_AABB_HPP_ */
