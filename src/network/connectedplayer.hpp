#ifndef SRC_NETWORK_CONNECTEDPLAYER_HPP
#define SRC_NETWORK_CONNECTEDPLAYER_HPP
#include <iostream>
#include <glm/glm.hpp>
class ConnectedPlayer{
public:
    std::string name;
    glm::vec3 position;
    int id;
    uint8_t team;
    ConnectedPlayer(std::string name,glm::vec3 position,int id,uint8_t team);
};
#endif