#version 330 core
in vec3 outUV;
out vec4 outColor;
uniform samplerCube textureid;

void main(){
    vec4 c=texture(textureid,outUV);
    outColor=c;
}