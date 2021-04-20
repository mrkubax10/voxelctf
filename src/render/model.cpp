/*
 * model.cpp
 *
 *  Created on: 8 kwi 2020
 *      Author: kuba
 */

#include "model.hpp"
#include <GL/glew.h>
#include <GL/gl.h>
Model::Model(){
	Model::pitch=0;
	Model::yaw=0;
	Model::roll=0;
	glGenVertexArrays(1,&mesh.VAO);
	glGenBuffers(1,&mesh.VBO);
	glGenBuffers(1,&mesh.EBO);
	glGenBuffers(1,&mesh.TBO);
}
Model::Model(std::vector<float> verts,std::vector<float> uvs,std::vector<int> indices){
	Model::pitch=0;
	Model::yaw=0;
	Model::roll=0;
	Model::indicesCount=indices.size();
	glGenVertexArrays(1,&mesh.VAO);
	glGenBuffers(1,&mesh.VBO);
	glGenBuffers(1,&mesh.EBO);
	glGenBuffers(1,&mesh.TBO);
	glBindVertexArray(mesh.VAO);
	glBindBuffer(GL_ARRAY_BUFFER,mesh.VBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(float)*verts.size(),verts.data(),GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
	glBindBuffer(GL_ARRAY_BUFFER,mesh.TBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(float)*uvs.size(),uvs.data(),GL_DYNAMIC_DRAW);
	glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,2*sizeof(float),(void*)0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,mesh.EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(int)*indices.size(),indices.data(),GL_DYNAMIC_DRAW);
	glBindVertexArray(0);
	Model::scale=glm::vec3(1,1,1);
	Model::generateTransform();
}
void Model::generateTransform(){
	Model::transformation=glm::mat4(1);
	Model::transformation=glm::translate(Model::transformation,Model::position);
	Model::transformation=glm::scale(Model::transformation,Model::scale);
}
void Model::translate(glm::vec3 pos){
	Model::position=pos;
	Model::generateTransform();
}
void Model::setScale(glm::vec3 s){
	Model::scale=s;
	Model::generateTransform();
}
void Model::rotate(float pitch,float yaw,float roll){
	Model::pitch=pitch;
	Model::yaw=yaw;
	Model::roll=roll;
	Model::generateTransform();
}
void Model::draw(ShaderProgram program,Camera cam,unsigned int mode){
	program.use();
	glBindVertexArray(mesh.VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,mesh.EBO);
	glBindBuffer(GL_ARRAY_BUFFER,mesh.VBO);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER,mesh.TBO);
	glEnableVertexAttribArray(1);
	

	program.setMat4("projection",cam.getProjection());
	program.setMat4("transform",Model::transformation);
	program.setMat4("view",cam.getView());
	program.setInt("textureid",0);
	glDrawElements(mode,Model::indicesCount,GL_UNSIGNED_INT,0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

}
