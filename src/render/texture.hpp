#ifndef SRC_RENDER_TEXTURE_HPP
#define SRC_RENDER_TEXTURE_HPP
#include <SDL2/SDL.h>
class Texture{
    unsigned int id;
    int w,h;
public:
    Texture();
    void loadFromSurface(SDL_Surface* surf);
    void use();
    unsigned int getID();
    int getW();
    int getH();
    void destroy();
    void updateSize();
};
#endif