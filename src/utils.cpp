/*
 * utils.cpp
 *
 *  Created on: 13 sty 2020
 *      Author: jacek
 */

#include "utils.hpp"
#include <GL/glew.h>
#include <GL/gl.h>
void renderDraw(SDL_Renderer *render,SDL_Texture *tex,int x,int y){
	rect.x=x;
	rect.y=y;
	SDL_QueryTexture(tex,0,0,&rect.w,&rect.h);
	SDL_RenderCopy(render,tex,0,&rect);
}
void renderDrawScaled(SDL_Renderer *render,SDL_Texture *tex,int x,int y,int w,int h){
	rect.x=x;
	rect.y=y;
	rect.w=w;
	rect.h=h;
	SDL_RenderCopy(render,tex,0,&rect);

}
std::vector<std::string> split(std::string str,char ch){
	std::vector<std::string> out;
	std::stringstream s(str);
	std::string e;
	while(getline(s,e,ch)){
		out.push_back(e);
	}
	return out;
}
std::string stringToLower(std::string str){
	std::string out;
	for(int i=0; i<str.length(); i++){
		out+=std::tolower(str[i]);
	}
	return out;
}
bool fileExists(std::string name){
	FILE* file=fopen(name.c_str(),"r");
	if(file){
		fclose(file);
		return true;
	}else{
		return false;
	}
}
Model createBoxModel(){
	std::vector<float> verts={
		0.0f,1.0f,1.0f,
		0.0f,0.0f,1.0f,
		1.0f,0.0f,1.0f,
		1.0f,1.0f,1.0f,
		1.0f,1.0f,1.0f,
		1.0f,0.0f,1.0f,
		1.0f,0.0f,0.0f,
		1.0f,1.0f,0.0f,
		0.0f,1.0f,0.0f,
		0.0f,0.0f,0.0f,
		1.0f,0.0f,0.0f,
		1.0f,1.0f,0.0f,
		0.0f,1.0f,1.0f,
		0.0f,0.0f,1.0f,
		0.0f,0.0f,0.0f,
		0.0f,1.0f,0.0f,
		0.0f,1.0f,0.0f,
		0.0f,1.0f,1.0f,
		1.0f,1.0f,1.0f,
		1.0f,1.0f,0.0f,
		0.0f,0.0f,0.0f,
		0.0f,0.0f,1.0f,
		1.0f,0.0f,1.0f,
		1.0f,0.0f,0.0f,
	};
	std::vector<int> indices={
		0,1,2,2,0,3,
		4,5,6,6,4,7,
		8,9,10,10,8,11,
		12,13,14,14,12,15,
		16,17,18,18,16,19,
		20,21,22,22,20,23
	};
	std::vector<float> uvs;
	for(int i=0; i<verts.size()/3/4; i++){
		uvs.push_back(0.0f);
		uvs.push_back(0.0f);
		uvs.push_back(0.0f);
		uvs.push_back(1.0f);
		uvs.push_back(1.0f);
		uvs.push_back(1.0f);
		uvs.push_back(1.0f);
		uvs.push_back(0.0f);
	}
	Model box(verts,uvs,indices);
	return box;
}
bool findChunkInVector(std::vector<glm::vec2> vec,glm::vec2 v){
	for(int i=0; i<vec.size(); i++){
		if(vec[i]==v){
			return true;
		}
	}
	return false;
}