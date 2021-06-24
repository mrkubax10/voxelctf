/*
 * Renderer.hpp
 *
 *  Created on: 7 kwi 2020
 *      Author:
 */

#ifndef SRC_RENDER_Renderer_HPP_
#define SRC_RENDER_Renderer_HPP_
#include "shaderprogram.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "camera.hpp"
#include "texture.hpp"
enum RendererFlags{
	NONE,FLIP_HORIZONTALLY,FLIP_VERTICALLY
};
class Renderer {
	unsigned int vao,vbo,tbo,ebo;
	Camera* camera;
	glm::mat4 transformation;
	ShaderProgram textured,colored;
public:
	Renderer(int windowW,int windowH,ShaderProgram s1,ShaderProgram s2);
	void drawTexturedRect(ShaderProgram program,Texture* texture,glm::vec2 pos,glm::vec2 scale);
	void drawColoredRect(ShaderProgram program,glm::vec4 color,glm::vec2 pos,glm::vec2 scale=glm::vec2(1,1));
	void drawTexturedRect(Texture* texture,glm::vec2 pos,glm::vec2 scale);
	void drawColoredRect(glm::vec4 color,glm::vec2 pos,glm::vec2 scale=glm::vec2(1,1));
	void drawTexturedRect(Texture* texture,glm::vec2 pos);
	void drawTexturedRect(Texture* texture,glm::vec2 pos,uint8_t flags);
	void update(int windowW,int windowH);
	void destroy();
};

#endif /* SRC_RENDER_Renderer_HPP_ */
