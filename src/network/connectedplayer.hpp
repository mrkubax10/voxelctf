#ifndef SRC_NETWORK_CONNECTEDPLAYER_HPP
#define SRC_NETWORK_CONNECTEDPLAYER_HPP
#include <iostream>
#include <glm/glm.hpp>
#include <SDL2/SDL.h>
class App;
class ConnectedPlayer{
public:
    std::string name;
    glm::vec3 position;
    int id;
    uint8_t team;
    SDL_Texture* nameTexture;
    ConnectedPlayer(std::string name,glm::vec3 position,int id,uint8_t team,App* app);
};
#endif