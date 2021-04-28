#version 330 core
layout(location=0) in vec2 inPos;
layout(location=1) in vec2 inUV;
out vec2 outUV;
uniform mat4 projection;
uniform mat4 transform;
void main(){
	gl_Position=projection*transform*vec4(inPos.x,inPos.y,0,1);
	outUV=inUV;
}