#include "rendertexture.hpp"
#include <GL/glew.h>
#include <GL/gl.h>
#include <iostream>
RenderTexture::RenderTexture(int w,int h){
    RenderTexture::w=w;
    RenderTexture::h=h;
    glGenFramebuffers(1,&fbo);
    glBindFramebuffer(GL_FRAMEBUFFER,fbo);
    RenderTexture::texture=new Texture();
    texture->use();
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,w,h,0,GL_RGB,GL_UNSIGNED_BYTE,0);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,texture->getID(),0);
    texture->updateSize();
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER)!=GL_FRAMEBUFFER_COMPLETE){
        std::cout<<"(Warn) [RenderTexture] Framebuffer incomplete"<<std::endl;
    }
    glBindFramebuffer(GL_FRAMEBUFFER,0);
}
void RenderTexture::use(){
    glBindTexture(GL_TEXTURE_2D,0);
    glBindFramebuffer(GL_FRAMEBUFFER,fbo);
    glViewport(0,0,w,h);
}
void RenderTexture::useDefault(int windoww,int windowh){
    glBindFramebuffer(GL_FRAMEBUFFER,0);
    glViewport(0,0,windoww,windowh);
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