#include "chat.hpp"
#include "../framework/app.hpp"
Chat::Chat(int x,int y,SDL_Renderer* render,TTF_Font* font,App* app){
    Chat::x=x;
    Chat::y=y;
    Chat::render=render;
    Chat::w=0;
    Chat::h=0;
    Chat::posy=0;
    Chat::font=font;
    Chat::enteringMessage=false;
    Chat::app=app;
    SDL_Surface* surf=TTF_RenderText_Blended(font,"",{0,0,0});
    Chat::messageTexture=SDL_CreateTextureFromSurface(render,surf);
    SDL_FreeSurface(surf);
    Chat::textfieldOpened=false;
    Chat::messageBuffer="";
    Chat::visible=true;
}
void Chat::draw(){
    Chat::posy=y;
    for(int i=0; i<Chat::chatEntries.size(); i++){
        for(int a=0; a<Chat::chatEntries[i].textures.size(); a++){
            SDL_QueryTexture(Chat::chatEntries[i].textures[a],0,0,&w2,&h2);
            renderDraw(Chat::render,Chat::chatEntries[i].textures[a],0,Chat::posy);
        }
        Chat::posy+=h2+2;
    }
    if(Chat::enteringMessage){
        guiRect.x=Chat::x;
        guiRect.y=400;
        guiRect.w=200;
        guiRect.h=50;
        SDL_SetRenderDrawColor(Chat::render,100,100,100,255);
        SDL_RenderFillRect(Chat::render,&guiRect);
        if(Chat::messageBuffer.length()>0){
            SDL_QueryTexture(Chat::messageTexture,0,0,&guiRect.w,&guiRect.h);
            SDL_RenderCopy(Chat::render,Chat::messageTexture,0,&guiRect);
        }
    }
}
void Chat::addEntry(std::string str){
    Chat::chatEntries.push_back({str,SDL_GetTicks()});
    SDL_Surface* surf=TTF_RenderText_Blended(Chat::font,str.c_str(),{0,0,0});
    Chat::chatEntries.back().textures.push_back(SDL_CreateTextureFromSurface(Chat::render,surf));
    SDL_FreeSurface(surf);
}
void Chat::update(SDL_Event* ev){
    if(ev->type==SDL_TEXTINPUT && Chat::enteringMessage && !Chat::textfieldOpened){
        Chat::messageBuffer+=ev->text.text;
        SDL_DestroyTexture(Chat::messageTexture);
        SDL_Surface* surf=TTF_RenderText_Blended(Chat::font,Chat::messageBuffer.c_str(),{0,0,0});
        Chat::messageTexture=SDL_CreateTextureFromSurface(Chat::render,surf);
        SDL_FreeSurface(surf);
    }
    if(Chat::textfieldOpened)
        Chat::textfieldOpened=false;
    if(ev->type==SDL_KEYDOWN && !Chat::enteringMessage){
        if(ev->key.keysym.scancode==app->getSettings()->keys.chat){
            Chat::enteringMessage=true;
            Chat::textfieldOpened=true;
        }
    }
    if(ev->type==SDL_KEYDOWN && Chat::enteringMessage){
        if(ev->key.keysym.scancode==SDL_SCANCODE_RETURN){
            if(Chat::messageBuffer.length()>0){
                
                Chat::addEntry(app->getUsername()+": "+Chat::messageBuffer);
                Chat::app->getServerConnection()->sendChatMessage(Chat::messageBuffer);
                Chat::enteringMessage=false;
                Chat::messageBuffer="";
            }
        }
        if(ev->key.keysym.scancode==SDL_SCANCODE_ESCAPE){
            Chat::messageBuffer="";
            Chat::enteringMessage=false;
        }
        if(ev->key.keysym.scancode==SDL_SCANCODE_BACKSPACE){
            if(Chat::messageBuffer.length()>0){
                Chat::messageBuffer.pop_back();
                SDL_DestroyTexture(Chat::messageTexture);
                SDL_Surface* surf;
                if(Chat::messageBuffer=="")
                    surf=TTF_RenderText_Blended(Chat::font,"",{0,0,0});
                else
                    surf=TTF_RenderText_Blended(Chat::font,Chat::messageBuffer.c_str(),{0,0,0});
                Chat::messageTexture=SDL_CreateTextureFromSurface(Chat::render,surf);
                SDL_FreeSurface(surf);
            }
        }
    }
    
}
void Chat::updateEntries(){
    for(int i=0; i<Chat::chatEntries.size(); i++){
        if(Chat::chatEntries[i].sendTime+10000<=SDL_GetTicks()){
            for(int a=0; a<Chat::chatEntries[i].textures.size(); a++)
                SDL_DestroyTexture(Chat::chatEntries[i].textures[a]);
            Chat::chatEntries.erase(Chat::chatEntries.begin()+i);
        }
    }
}
void Chat::setEnteringMessage(bool enteringMessage){
    Chat::enteringMessage=enteringMessage;
}
bool Chat::isEnteringMessage(){
    return Chat::enteringMessage;
}