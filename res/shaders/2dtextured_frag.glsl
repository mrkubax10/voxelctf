#version 330 core
in vec2 outUV;
out vec4 outColor;
uniform sampler2D textureid;
void main(){
	vec4 c=texture(textureid,outUV);
	if(c.a==0)
		discard;
	outColor=c;
}