#include "skybox.hpp"
#include <GL/glew.h>
#include <GL/gl.h>
Skybox::Skybox(){
    Skybox::surfaces=new SDL_Surface*[6];
    Skybox::surfaces[0]=IMG_Load("res/textures/skybox/right.png");
    Skybox::surfaces[1]=IMG_Load("res/textures/skybox/left.png");
    Skybox::surfaces[2]=IMG_Load("res/textures/skybox/top.png");
    Skybox::surfaces[3]=IMG_Load("res/textures/skybox/bottom.png");
    Skybox::surfaces[4]=IMG_Load("res/textures/skybox/back.png");
    Skybox::surfaces[5]=IMG_Load("res/textures/skybox/front.png");
    unsigned int textureFormat=0;
    glGenTextures(1,&textureid);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP,textureid);
    for(int i=0; i<5+1; i++){
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+i,0,GL_RGB,surfaces[i]->w,surfaces[i]->h,0,GL_RGB,GL_UNSIGNED_BYTE,surfaces[i]->pixels);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glGenVertexArrays(1,&vao);
    glGenBuffers(1,&vbo);
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
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glBufferData(GL_ARRAY_BUFFER,sizeof(verts)*sizeof(float),verts,GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
}
void Skybox::draw(ShaderProgram program,Camera cam){
    glDepthMask(GL_FALSE);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP,textureid);
    program.use();
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glEnableVertexAttribArray(0);
    program.setMat4("projection",cam.getProjection());
    program.setInt("textureid",0);
    program.setMat4("view",glm::mat4(glm::mat3(cam.getView())));
    glDrawArrays(GL_TRIANGLES,0,36);
    glDisableVertexAttribArray(0);
    glDepthMask(GL_TRUE);
}
void Skybox::destroy(){
    for(int i=0; i<5+1; i++){
        SDL_FreeSurface(Skybox::surfaces[i]);
    }
    delete[] surfaces;
    glDeleteTextures(1,&textureid);
    glDeleteVertexArrays(1,&vao);
    glDeleteBuffers(1,&vbo); 
}
