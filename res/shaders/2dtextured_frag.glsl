#version 330 core
in vec2 outUV;
out vec4 outColor;
uniform sampler2D textureid;
uniform int flipHorizontally;
uniform int flipVertically;
void main(){
	vec2 uv=outUV;
	if(flipHorizontally==1)
		uv.x=1-uv.x;
	if(flipVertically==1)
		uv.y=1-uv.y;
	vec4 c=texture(textureid,uv);
	if(c.a==0)
		discard;
	outColor=c;
}