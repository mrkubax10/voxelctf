#version 330 core
in vec2 outUV;
out vec4 outColor;
uniform sampler2D textureid;
void main(){
    vec4 frag=texture(textureid,outUV);
    outColor=vec4(frag.r,frag.g,frag.b,1);
}