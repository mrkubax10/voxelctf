#ifndef SRC_WORLD_TEXTUREATLAS_HPP
#define SRC_WORLD_TEXTUREATLAS_HPP
#include <map>
#include "block.hpp"
#include "../managers/resourcemanager.hpp"
#include <fstream>
#include "../utils.hpp"
#include "../render/texture.hpp"
#include "../render/renderer.hpp"
struct TextureAtlasBlockUV{
    float left,right,top,bottom,back,front;
};
class TextureAtlas{
    SDL_Surface* surface;
    Texture* texture;
    std::map<BlockType,TextureAtlasBlockUV> blockUVs;
    Renderer* renderer;
    int maxTextureSize;
    int textureSize;
    float textureBlockSize;
public:
    TextureAtlas(Renderer* renderer);
    void generateTextureAtlas(ResourceManager *man);
    TextureAtlasBlockUV getBlockUV(uint8_t type);
    void use();
    float getTextureBlockSize();
    Texture* getTexture();
};
#endif