#include "texture.hpp"
#include <GL/glew.h>
#include <GL/gl.h>
#include <iostream>
Texture::Texture(){
    glGenTextures(1,&id);
    Texture::w=0;
    Texture::h=0;
}
void Texture::loadFromSurface(SDL_Surface* surf){
    if(surf==0)
        return;
    Texture::use();
    
    int internalFormat=0,pixelFormat=0,unpackAlignment=4;
    if(surf->format->format==373694468){
        internalFormat=GL_RGBA;
        pixelFormat=0x80E1;
    }
    else if(surf->format->format==SDL_PIXELFORMAT_RGBA8888){
        internalFormat=GL_RGBA;
        pixelFormat=GL_RGBA;
    }
    else if(surf->format->format==SDL_PIXELFORMAT_ARGB8888){
        internalFormat=GL_RGBA;
        pixelFormat=0x80E1;
    }
    else if(surf->format->format==376840196){
        internalFormat=GL_RGBA;
        pixelFormat=GL_RGBA;
    }
    else if(surf->format->format==SDL_PIXELFORMAT_INDEX8){
        internalFormat=GL_RGBA;
        pixelFormat=GL_ALPHA;
        unpackAlignment=1;
        std::cout<<(int)surf->format->BytesPerPixel<<std::endl;
    }
    else
        std::cout<<"(Warn) [Texture] Invalid pixel format: "<<surf->format->format<<std::endl;
    glTexImage2D(GL_TEXTURE_2D,0,internalFormat,surf->w,surf->h,0,pixelFormat,GL_UNSIGNED_BYTE,surf->pixels);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glPixelStorei(GL_UNPACK_ALIGNMENT,unpackAlignment);
    glPixelStorei(GL_UNPACK_ROW_LENGTH,0);
    Texture::w=surf->w;
    Texture::h=surf->h;
}
void Texture::use(){
    glBindTexture(GL_TEXTURE_2D,id);
}
unsigned int Texture::getID(){
    return id;
}
int Texture::getW(){
    return w;
}
int Texture::getH(){
    return h;
}
void Texture::destroy(){
    glDeleteTextures(1,&id);
}