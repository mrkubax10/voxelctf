#version 330 core
layout(location=0) in vec3 inPos;
layout(location=1) in vec2 inUV;
out vec2 outUV;
uniform mat4 projection;
uniform mat4 view;
uniform int inTime;
void main(){
	//inPos.y+=sin(inTime*0.0001);
	gl_Position=projection*view*vec4(inPos,1);
	outUV=inUV;
}