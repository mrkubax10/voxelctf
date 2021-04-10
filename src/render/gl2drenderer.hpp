/*
 * gl2drenderer.hpp
 *
 *  Created on: 7 kwi 2020
 *      Author:
 */

#ifndef SRC_RENDER_GL2DRENDERER_HPP_
#define SRC_RENDER_GL2DRENDERER_HPP_
#include "shaderprogram.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "model.hpp"
#include <SDL2/SDL.h>
class GL2DRenderer {
	SDL_Window* window;
	SDL_Renderer* render;
	SDL_Texture* texture;
	int w,h;
	unsigned int vao,vbo,tbo,ebo;
public:
	GL2DRenderer(SDL_Window* window,SDL_Renderer* render);
	void start();
	void finish(ShaderProgram program);
	void setTextureSize(int w,int h);
	void destroy();
};

#endif /* SRC_RENDER_GL2DRENDERER_HPP_ */
