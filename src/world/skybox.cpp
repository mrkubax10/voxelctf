#include "skybox.hpp"
#include <GL/glew.h>
#include <GL/gl.h>
Skybox::Skybox(){
    glGenVertexArrays(1,&vao);
    glGenBuffers(1,&vbo);
    glGenBuffers(1,&colorBuffer);
    
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
    for(int i=0; i<4*6*3; i+=3){
        Skybox::colorValues.push_back(0);
        Skybox::colorValues.push_back(0);
        Skybox::colorValues.push_back(1);
    }
    glBindBuffer(GL_ARRAY_BUFFER,colorBuffer);
    glBufferData(GL_ARRAY_BUFFER,Skybox::colorValues.size()*sizeof(float),Skybox::colorValues.data(),GL_STATIC_DRAW);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
}
void Skybox::draw(ShaderProgram program,Camera cam){
    glDepthMask(GL_FALSE);
    glActiveTexture(GL_TEXTURE0);
    program.use();
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER,colorBuffer);
    glEnableVertexAttribArray(1);
    program.setMat4("projection",cam.getProjection());
    program.setMat4("view",glm::mat4(glm::mat3(cam.getView())));
    glDrawArrays(GL_TRIANGLES,0,36);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDepthMask(GL_TRUE);
}
void Skybox::destroy(){
    glDeleteVertexArrays(1,&vao);
    glDeleteBuffers(1,&vbo); 
    glDeleteBuffers(1,&colorBuffer);
}
