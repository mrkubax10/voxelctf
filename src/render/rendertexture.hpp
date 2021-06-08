#ifndef SRC_RENDER_RENDERTEXTURE_HPP
#define SRC_RENDER_RENDERTEXTURE_HPP
#include "texture.hpp"
class App;
class RenderTexture{
    unsigned int fbo;
    Texture* texture;
    int w,h;
public:
    RenderTexture(int w,int h);
    void use();
    static void useDefault(int windoww,int windowh);
    void resize(int w,int h);
    unsigned int getNative();
    Texture* getTexture();
    int getW();
    int getH();
    void destroy();
};
#endif