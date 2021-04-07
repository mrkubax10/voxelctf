#include "connectedplayer.hpp"
ConnectedPlayer::ConnectedPlayer(std::string name,glm::vec3 position,int id,uint8_t team){
    ConnectedPlayer::name=name;
    ConnectedPlayer::position=position;
    ConnectedPlayer::id=id;
    ConnectedPlayer::team=team;
}