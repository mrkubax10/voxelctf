#version 330 core
layout(location=0) in vec2 inPos;
layout(location=1) in vec2 inUV;
out vec2 outUV;
uniform mat4 projection;
uniform mat4 transform;
uniform mat4 view;
void main(){
	gl_Position=vec4(inPos.x,inPos.y,0,1);
	outUV=inUV;
}