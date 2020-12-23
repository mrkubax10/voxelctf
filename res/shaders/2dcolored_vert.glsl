#version 330 core
layout(location=0) in vec2 inPos;
uniform mat4 projection;
uniform mat4 transform;
void main(){
	gl_Position=vec4(inPos.x,inPos.y,0,1);
}