#include "connectedplayer.hpp"
ConnectedPlayer::ConnectedPlayer(std::string name,glm::vec3 position,int id){
    ConnectedPlayer::name=name;
    ConnectedPlayer::position=position;
    ConnectedPlayer::id=id;
}