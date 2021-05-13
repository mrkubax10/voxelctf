#include "hud.hpp"
#include "../framework/app.hpp"
HUD::HUD(Renderer* renderer,Player* player,TTF_Font* font,App* app){
    HUD::renderer=renderer;
    HUD::player=player;
    HUD::font=font;
    HUD::app=app;
    SDL_Surface* surf=TTF_RenderText_Blended(font,std::string(std::to_string(player->getHP())+"/"+std::to_string(player->getMaxHP())).c_str(),{255,255,255});
    HUD::textureHP=new Texture();
    HUD::textureHP->loadFromSurface(surf);
    SDL_FreeSurface(surf);
    HUD::x=0;
    HUD::y=0;
    HUD::visible=true;
}
void HUD::draw(){
    renderer->drawTexturedRect(HUD::textureHP,glm::vec2(HUD::app->getWindowW()-HUD::textureHP->getW()-2,2),glm::vec2(HUD::textureHP->getW(),HUD::textureHP->getH()));
    if(HUD::player->playerHasFlag){
        renderer->drawTexturedRect(app->getResourceManager()->getNativeTexture("hud_flag"),glm::vec2(app->getWindowW()-app->getResourceManager()->getNativeTexture("hud_flag")->getW()-2,app->getWindowH()-app->getResourceManager()->getNativeTexture("hud_flag")->getH()-2),glm::vec2(app->getResourceManager()->getNativeTexture("hud_flag")->getW(),app->getResourceManager()->getNativeTexture("hud_flag")->getH()));
    }
}
void HUD::update(SDL_Event* ev){

}
void HUD::updateInfo(){
    SDL_Surface* surf=TTF_RenderText_Blended(font,std::string(std::to_string(player->getHP())+"/"+std::to_string(player->getMaxHP())).c_str(),{255,255,255});
    HUD::textureHP->loadFromSurface(surf);
    SDL_FreeSurface(surf);
}