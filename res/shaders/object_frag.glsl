#version 330 core
in vec2 outUV;
out vec4 outColor;
uniform sampler2D textureid;
uniform vec4 color;
void main(){
    //vec4 c=texture(textureid,outUV);
    //if(c.a==0)
    //    discard;
    outColor=vec4(0,1,0,1);
}