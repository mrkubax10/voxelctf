#include "connectedplayer.hpp"
#include "../framework/app.hpp"
ConnectedPlayer::ConnectedPlayer(std::string name,glm::vec3 position,int id,uint8_t team,App* app){
    ConnectedPlayer::name=name;
    ConnectedPlayer::position=position;
    ConnectedPlayer::id=id;
    ConnectedPlayer::team=team;
    SDL_Surface* surf=TTF_RenderText_Blended(app->getResourceManager()->getFont("default",15),name.c_str(),{255,255,255});
    ConnectedPlayer::nameTexture=SDL_CreateTextureFromSurface(app->getSDLRenderer(),surf);
    SDL_FreeSurface(surf);
}