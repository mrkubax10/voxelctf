/*
 * shaderprogram.cpp
 *
 *  Created on: 18 mar 2020
 *      Author: kuba
 */

#include "shaderprogram.hpp"
#include <GL/glew.h>
#include <GL/gl.h>
#include <fstream>
#include <sstream>
ShaderProgram::ShaderProgram(){
	ShaderProgram::program=glCreateProgram();
	ShaderProgram::vertex=glCreateShader(GL_VERTEX_SHADER);
	ShaderProgram::fragment=glCreateShader(GL_FRAGMENT_SHADER);
}
void ShaderProgram::loadFromFiles(std::string vfile,std::string ffile){
	std::string vSource="",fSource="";
	std::fstream file;
	file.open(vfile,std::ios::in);
	std::string line;
	while(getline(file,line)){
		vSource+=line+"\n";
	}
	file.close();
	file.clear();
	file.open(ffile,std::ios::in);
	while(getline(file,line)){
		fSource+=line+"\n";
	}
	file.close();
	const char* cVSource=vSource.c_str();
	const char* cFSource=fSource.c_str();
	int success;
	char log[512];
	glShaderSource(ShaderProgram::vertex,1,&cVSource,0);
	glCompileShader(ShaderProgram::vertex);
	glGetShaderiv(ShaderProgram::vertex,GL_COMPILE_STATUS,&success);
	if(!success){
		glGetShaderInfoLog(ShaderProgram::vertex,512,0,log);
		std::cout<<"(Warn) [ShaderProgram] Vertex shader compilation failed: "<<log<<std::endl;
	}
	glShaderSource(ShaderProgram::fragment,1,&cFSource,0);
	glCompileShader(ShaderProgram::fragment);
	glGetShaderiv(ShaderProgram::fragment,GL_COMPILE_STATUS,&success);
	if(!success){
		glGetShaderInfoLog(ShaderProgram::fragment,512,0,log);
		std::cout<<"(Warn) [ShaderProgram] Fragment shader compilation failed: "<<log<<std::endl;
	}
	glAttachShader(ShaderProgram::program,ShaderProgram::vertex);
	glAttachShader(ShaderProgram::program,ShaderProgram::fragment);
	glLinkProgram(ShaderProgram::program);
	glGetProgramiv(ShaderProgram::program,GL_LINK_STATUS,&success);
	if(!success){
		glGetProgramInfoLog(ShaderProgram::program,512,0,log);
		std::cout<<"(Warn) [ShaderProgram] Program linking failed: "<<log<<std::endl;
	}
}
void ShaderProgram::setInt(std::string name,int v){
glUniform1i(glGetUniformLocation(ShaderProgram::program,name.c_str()),v);
}
void ShaderProgram::setMat4(std::string name,glm::mat4 v){
	glUniformMatrix4fv(glGetUniformLocation(ShaderProgram::program,name.c_str()),1,GL_FALSE,&v[0][0]);
}
void ShaderProgram::use(){
	glUseProgram(program);
}
void ShaderProgram::setVec4(std::string name,glm::vec4 v){
	glUniform4fv(glGetUniformLocation(ShaderProgram::program,name.c_str()),4,&v[0]);
}
void ShaderProgram::destroy(){
	glDeleteShader(ShaderProgram::vertex);
	glDeleteShader(ShaderProgram::fragment);
	glDeleteProgram(ShaderProgram::program);
}
void ShaderProgram::setVec3(std::string name,glm::vec3 v){
	glUniform3fv(glGetUniformLocation(ShaderProgram::program,name.c_str()),3,&v[0]);
}