#version 330 core
in vec3 outColorValue;
out vec4 outColor;

void main(){
    outColor=vec4(outColorValue,1);
}