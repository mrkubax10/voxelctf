#ifndef SRC_WORLD_SKYBOX_HPP
#define SRC_WORLD_SKYBOX_HPP
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../render/shaderprogram.hpp"
#include "../render/fpscamera.hpp"
#include "../utils.hpp"
#include "../managers/resourcemanager.hpp"
class Skybox{
    unsigned int vao,vbo,texture;
    SDL_Surface** surfaces;
    SDL_Surface** rgb8888Surfaces;
public:
    Skybox(ResourceManager* man);
    void draw(ShaderProgram program,Camera cam);
    void destroy();
};
#endif