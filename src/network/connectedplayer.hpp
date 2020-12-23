#ifndef SRC_NETWORK_CONNECTEDPLAYER_HPP
#define SRC_NETWORK_CONNECTEDPLAYER_HPP
#include <iostream>
#include <glm/glm.hpp>
class ConnectedPlayer{
public:
    std::string name;
    glm::vec3 position;
    int id;
    ConnectedPlayer(std::string name,glm::vec3 position,int id);
};
#endif