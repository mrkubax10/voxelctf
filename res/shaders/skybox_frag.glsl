#version 330 core
in vec3 outUV;
out vec4 outColor;
uniform samplerCube textureid;
void main(){
    outColor=texture(textureid,outUV);
}