#include "chat.hpp"
Chat::Chat(int x,int y,SDL_Renderer* render,TTF_Font* font){
    Chat::x=x;
    Chat::y=y;
    Chat::render=render;
    Chat::w=0;
    Chat::h=0;
    Chat::posy=0;
    Chat::font=font;
}
void Chat::draw(){
    Chat::posy=y;
    for(int i=0; i<Chat::chatEntryTextures.size(); i++){
        SDL_QueryTexture(Chat::chatEntryTextures[i],0,0,&w2,&h2);
        renderDraw(Chat::render,Chat::chatEntryTextures[i],0,Chat::posy);
        Chat::posy+=h2+2;
    }
}
void Chat::addEntry(std::string str){
    Chat::chatEntries.push_back(str);
    SDL_Surface* surf=TTF_RenderText_Blended(font,str.c_str(),{0,0,0});
    Chat::chatEntryTextures.push_back(SDL_CreateTextureFromSurface(render,surf));
    SDL_FreeSurface(surf);
    Chat::chatEntryTime.push_back(SDL_GetTicks());
}
void Chat::update(SDL_Event* ev){
    
}
void Chat::updateEntries(){
    for(int i=0; i<Chat::chatEntries.size(); i++){
        if(Chat::chatEntryTime[i]+10000<=SDL_GetTicks()){
            Chat::chatEntries.erase(Chat::chatEntries.begin()+i);
            SDL_DestroyTexture(Chat::chatEntryTextures[i]);
            Chat::chatEntryTextures.erase(Chat::chatEntryTextures.begin()+i);
            Chat::chatEntryTime.erase(Chat::chatEntryTime.begin()+i);
        }
    }
}