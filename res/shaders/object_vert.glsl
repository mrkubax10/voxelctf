#version 330 core
layout(location=0) in vec3 inPos;
layout(location=1) in vec2 inUV;
out vec2 outUV;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 transform;
void main(){
    gl_Position=projection*view*transform*vec4(inPos,1.0);
    outUV=inUV;
}