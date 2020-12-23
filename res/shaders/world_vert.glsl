#version 330 core
layout(location=0) in vec3 inPos;
layout(location=1) in vec2 inUV;
layout(location=2) in float inLightValue;
out vec2 outUV;
out float outLightValue;
uniform mat4 projection;
uniform mat4 view;
void main(){
	gl_Position=projection*view*vec4(inPos,1);
	outUV=inUV;
	outLightValue=inLightValue;
}