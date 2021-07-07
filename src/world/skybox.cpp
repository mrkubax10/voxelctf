#include "skybox.hpp"
#include <GL/glew.h>
#include <GL/gl.h>
Skybox::Skybox(ResourceManager* man){
    glGenVertexArrays(1,&vao);
    glGenBuffers(1,&vbo);
    glGenTextures(1,&texture);
    
    float verts[]={
        
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
        1.0f,  1.0f, -1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
        1.0f, -1.0f,  1.0f
    };
    Skybox::surfaces=new SDL_Surface*[6];
    Skybox::rgb8888Surfaces=new SDL_Surface*[6];
    surfaces[0]=man->getSurface("skybox/right");
    surfaces[1]=man->getSurface("skybox/left");
    surfaces[2]=man->getSurface("skybox/top");
    surfaces[3]=man->getSurface("skybox/bottom");
    surfaces[4]=man->getSurface("skybox/back");
    surfaces[5]=man->getSurface("skybox/front");
    glBindTexture(GL_TEXTURE_CUBE_MAP,texture);
    for(int i=0; i<6; i++){
        rgb8888Surfaces[i]=SDL_ConvertSurfaceFormat(surfaces[i],SDL_PIXELFORMAT_RGB888,0);
        SDL_FreeSurface(surfaces[i]);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+i,0,GL_RGB,2048,2048,0,0x80E1,GL_UNSIGNED_BYTE,rgb8888Surfaces[i]->pixels);
        SDL_FreeSurface(rgb8888Surfaces[i]);
    }
    delete[] Skybox::surfaces;
    delete[] Skybox::rgb8888Surfaces;
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glBufferData(GL_ARRAY_BUFFER,sizeof(verts)*sizeof(float),verts,GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
}
void Skybox::draw(ShaderProgram program,Camera cam){
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP,texture);
    glDepthMask(GL_FALSE);
    program.use();
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glEnableVertexAttribArray(0);
    program.setMat4("projection",cam.getProjection());
    program.setMat4("view",glm::mat4(glm::mat3(cam.getView())));
    program.setInt("textureid",0);
    glDrawArrays(GL_TRIANGLES,0,36);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDepthMask(GL_TRUE);
}
void Skybox::destroy(){
    glDeleteVertexArrays(1,&vao);
    glDeleteBuffers(1,&vbo); 
}
