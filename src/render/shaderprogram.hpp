/*
 * shaderprogram.hpp
 *
 *  Created on: 18 mar 2020
 *      Author: kuba
 */

#ifndef SRC_RENDER_SHADERPROGRAM_HPP_
#define SRC_RENDER_SHADERPROGRAM_HPP_
#include <glm/glm.hpp>
#include <iostream>
class ShaderProgram {
	unsigned int program,vertex,fragment;
public:
	ShaderProgram();
	void loadFromFiles(std::string vfile,std::string ffile);
	void setInt(std::string name,int v);
	void setMat4(std::string name,glm::mat4 v);
	void setVec2(std::string name,glm::vec2 v);
	void setVec3(std::string name,glm::vec3 v);
	void setVec4(std::string name,glm::vec4 v);
	void use();
	void destroy();
};

#endif /* SRC_RENDER_SHADERPROGRAM_HPP_ */
