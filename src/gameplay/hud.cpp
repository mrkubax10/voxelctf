#include "hud.hpp"
#include "../framework/app.hpp"
HUD::HUD(SDL_Renderer* render,Player* player,TTF_Font* font,App* app){
    HUD::render=render;
    HUD::player=player;
    HUD::font=font;
    HUD::app=app;

    SDL_Surface* surf=TTF_RenderText_Blended(font,std::string(std::to_string(player->getHP())+"/"+std::to_string(player->getMaxHP())).c_str(),{255,255,255});
    HUD::textureHP=SDL_CreateTextureFromSurface(render,surf);
    SDL_FreeSurface(surf);
    HUD::x=0;
    HUD::y=0;
    HUD::visible=true;
}
void HUD::draw(){
    SDL_QueryTexture(HUD::textureHP,0,0,&guiRect.w,&guiRect.h);
    guiRect.x=HUD::app->getWindowW()-guiRect.w-2;
    guiRect.y=2;
    SDL_RenderCopy(HUD::render,HUD::textureHP,0,&guiRect);
    if(HUD::player->playerHasFlag){
        SDL_QueryTexture(app->getResourceManager()->getTexture("hud_flag"),0,0,&guiRect.w,&guiRect.h);
        guiRect.x=app->getWindowW()-guiRect.w-2;
        guiRect.y=app->getWindowH()-guiRect.h-2;
        SDL_RenderCopy(HUD::render,app->getResourceManager()->getTexture("hud_flag"),0,&guiRect);
    }
}
void HUD::update(SDL_Event* ev){

}
void HUD::updateInfo(){
    SDL_Surface* surf=TTF_RenderText_Blended(font,std::string(std::to_string(player->getHP())+"/"+std::to_string(player->getMaxHP())).c_str(),{255,255,255});
    SDL_DestroyTexture(HUD::textureHP);
    HUD::textureHP=SDL_CreateTextureFromSurface(render,surf);
    SDL_FreeSurface(surf);
}