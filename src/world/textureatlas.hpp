#ifndef SRC_WORLD_TEXTUREATLAS_HPP
#define SRC_WORLD_TEXTUREATLAS_HPP
#include <SDL2/SDL.h>
#include <map>
#include "block.hpp"
#include "../managers/resourcemanager.hpp"
#include <fstream>
#include "../utils.hpp"
struct TextureAtlasBlockUV{
    float left,right,top,bottom,back,front;
};
class TextureAtlas{
    SDL_Texture* texture;
    std::map<BlockType,TextureAtlasBlockUV> blockUVs;
    SDL_Renderer* render;
    int maxTextureSize;
    int textureSize;
    float textureBlockSize;
public:
    TextureAtlas(SDL_Renderer* render);
    void generateTextureAtlas(ResourceManager *man);
    TextureAtlasBlockUV getBlockUV(uint8_t type);
    void use();
    float getTextureBlockSize();
};
#endif