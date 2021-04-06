#ifndef SRC_WORLD_SKYBOX_HPP
#define SRC_WORLD_SKYBOX_HPP
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../render/shaderprogram.hpp"
#include "../render/fpscamera.hpp"
#include "../utils.hpp"
class Skybox{
    unsigned int vao,vbo,colorBuffer;
    std::vector<float> colorValues;
public:
    Skybox();
    void draw(ShaderProgram program,Camera cam);
    void destroy();
};
#endif