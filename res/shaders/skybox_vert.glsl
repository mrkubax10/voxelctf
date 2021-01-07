#version 330 core
layout(location=0) in vec3 inPos;
out vec3 outUV;
uniform mat4 projection;
uniform mat4 view;
void main(){
    gl_Position=projection*view*vec4(inPos,1);
    outUV=inPos;
}