#include "rendertexture.hpp"
#include <GL/glew.h>
#include <GL/gl.h>
#include <iostream>
RenderTexture::RenderTexture(int w,int h){
    RenderTexture::w=w;
    RenderTexture::h=h;
    glGenFramebuffers(1,&fbo);
    RenderTexture::texture=new Texture();
    glBindFramebuffer(GL_FRAMEBUFFER,fbo);
    texture->use();
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,w,h,0,GL_RGB,GL_UNSIGNED_BYTE,0);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,texture->getID(),0);
    glBindFramebuffer(GL_FRAMEBUFFER,0);
}
void RenderTexture::use(){
    glBindFramebuffer(GL_FRAMEBUFFER,fbo);
}
void RenderTexture::useDefault(){
    glBindFramebuffer(GL_FRAMEBUFFER,0);
}
void RenderTexture::resize(int w,int h){
    texture->use();
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,w,h,0,GL_RGB,GL_UNSIGNED_BYTE,0);
}
unsigned int RenderTexture::getNative(){
    return RenderTexture::fbo;
}
Texture* RenderTexture::getTexture(){
    return texture;
}
int RenderTexture::getW(){
    return RenderTexture::w;
}
int RenderTexture::getH(){
    return RenderTexture::h;
}
void RenderTexture::destroy(){
    glDeleteFramebuffers(1,&fbo);
    texture->destroy();
}