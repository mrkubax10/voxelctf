/*
 * gl2drenderer.cpp
 *
 *  Created on: 7 kwi 2020
 *      Author: kuba
 */

#include "gl2drenderer.hpp"
#include <GL/glew.h>
#include <GL/gl.h>

GL2DRenderer::GL2DRenderer(SDL_Window* window,SDL_Renderer* render){
	GL2DRenderer::window=window;
	GL2DRenderer::render=render;
	SDL_GetWindowSize(window,&w,&h);
	GL2DRenderer::texture=SDL_CreateTexture(GL2DRenderer::render,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,w,h);
	glGenVertexArrays(1,&vao);
	glGenBuffers(1,&vbo);
	glGenBuffers(1,&tbo);
	glGenBuffers(1,&ebo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER,vbo);
	float verts[]={
		-1,1,
		-1,-1,
		1,-1,
		1,1
	};
	glBufferData(GL_ARRAY_BUFFER,sizeof(verts),verts,GL_STATIC_DRAW);
	glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,0,(void*)0);
	glBindBuffer(GL_ARRAY_BUFFER,tbo);
	float uvs[]={
		0,0,
		0,1,
		1,1,
		1,0
	};
	glBufferData(GL_ARRAY_BUFFER,sizeof(uvs),uvs,GL_STATIC_DRAW);
	glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,0,(void*)0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo);
	int indices[]={
		0,1,2,2,0,3
	};
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);
	
}
void GL2DRenderer::start(){
	SDL_SetRenderTarget(GL2DRenderer::render,GL2DRenderer::texture);
}
void GL2DRenderer::finish(ShaderProgram program){
	if(glIsEnabled(GL_DEPTH_TEST))
		glDisable(GL_DEPTH_TEST);
	SDL_SetRenderTarget(GL2DRenderer::render,0);
	SDL_GL_BindTexture(GL2DRenderer::texture,0,0);
	program.use();
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER,vbo);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER,tbo);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo);
	program.setInt("textureid",0);
	glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

void GL2DRenderer::setTextureSize(int x,int y){
	SDL_DestroyTexture(GL2DRenderer::texture);
	GL2DRenderer::texture=SDL_CreateTexture(GL2DRenderer::render,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,x,y);
}
void GL2DRenderer::destroy(){
	SDL_DestroyTexture(GL2DRenderer::texture);
	glDeleteBuffers(1,&vbo);
	glDeleteBuffers(1,&tbo);
	glDeleteBuffers(1,&ebo);
	glDeleteVertexArrays(1,&vao);	
}