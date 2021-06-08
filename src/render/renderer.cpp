/*
 * Renderer.cpp
 *
 *  Created on: 7 kwi 2020
 *      Author: kuba
 */

#include "renderer.hpp"
#include <GL/glew.h>
#include <GL/gl.h>

Renderer::Renderer(int windowW,int windowH,ShaderProgram s1,ShaderProgram s2){
	glGenVertexArrays(1,&vao);
	glGenBuffers(1,&vbo);
	glGenBuffers(1,&tbo);
	glGenBuffers(1,&ebo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER,vbo);
	float verts[]={
		0,0,
		0,1,
		1,1,
		1,0
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
	Renderer::camera=new Camera();
	camera->setProjection(glm::ortho(0.0f,(float)windowW,(float)windowH,0.0f));
	Renderer::transformation=glm::mat4(1);
	Renderer::textured=s1;
	Renderer::colored=s2;
}
void Renderer::drawTexturedRect(ShaderProgram program,Texture* texture,glm::vec2 pos,glm::vec2 scale){
	
	if(glIsEnabled(GL_DEPTH_TEST))
		glDisable(GL_DEPTH_TEST);
	program.use();
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER,vbo);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER,tbo);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo);
	program.setMat4("projection",camera->getProjection());
	program.setInt("textureid",0);
	texture->use();
	Renderer::transformation=glm::mat4(1);
	Renderer::transformation=glm::translate(Renderer::transformation,glm::vec3(pos.x,pos.y,0));
	Renderer::transformation=glm::scale(Renderer::transformation,glm::vec3(scale.x,scale.y,1));
	program.setMat4("transform",Renderer::transformation);
	
	glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}
void Renderer::drawColoredRect(ShaderProgram program,glm::vec4 color,glm::vec2 pos,glm::vec2 scale){
	if(glIsEnabled(GL_DEPTH_TEST))
		glDisable(GL_DEPTH_TEST);
	program.use();
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER,vbo);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo);
	program.setMat4("projection",camera->getProjection());
	program.setVec4("color",color);
	Renderer::transformation=glm::mat4(1);
	Renderer::transformation=glm::translate(Renderer::transformation,glm::vec3(pos.x,pos.y,0));
	Renderer::transformation=glm::scale(Renderer::transformation,glm::vec3(scale.x,scale.y,1));
	program.setMat4("transform",Renderer::transformation);
	glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
	glDisableVertexAttribArray(0);
}
void Renderer::drawTexturedRect(Texture* texture,glm::vec2 pos){
	Renderer::drawTexturedRect(textured,texture,pos,glm::vec2(texture->getW(),texture->getH()));
}
void Renderer::drawTexturedRect(Texture* texture,glm::vec2 pos,glm::vec2 scale){
	Renderer::drawTexturedRect(textured,texture,pos,scale);
}
void Renderer::drawColoredRect(glm::vec4 color,glm::vec2 pos,glm::vec2 scale){
	Renderer::drawColoredRect(colored,color,pos,scale);
}
void Renderer::update(int windowW,int windowH){
	camera->setProjection(glm::ortho(0.0f,(float)windowW,(float)windowH,0.0f));
}
void Renderer::destroy(){
	glDeleteBuffers(1,&vbo);
	glDeleteBuffers(1,&tbo);
	glDeleteBuffers(1,&ebo);
	glDeleteVertexArrays(1,&vao);	
}