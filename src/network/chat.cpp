#include "chat.hpp"
#include "../framework/app.hpp"
Chat::Chat(int x,int y,SDL_Renderer* render,TTF_Font* font,App* app){
    Chat::x=x;
    Chat::y=y;
    Chat::render=render;
    Chat::w=400;
    Chat::h=390;
    Chat::posy=0;
    Chat::font=font;
    Chat::enteringMessage=false;
    Chat::app=app;
    SDL_Surface* surf=TTF_RenderText_Blended(font," ",{0,0,0});
    Chat::messageTexture=SDL_CreateTextureFromSurface(render,surf);
    SDL_FreeSurface(surf);
    Chat::textfieldOpened=false;
    Chat::messageBuffer="";
    Chat::visible=true;
}
void Chat::draw(){
    
    if(Chat::enteringMessage){
        SDL_SetRenderDrawColor(Chat::render,100,100,100,200);
        guiRect.x=Chat::x;
        guiRect.y=Chat::y;
        guiRect.w=Chat::w;
        guiRect.h=Chat::h;
        SDL_RenderFillRect(Chat::render,&guiRect);
    }
    Chat::posy=3*15+10;
    if(!Chat::enteringMessage){
        int length=Chat::chatEntries.size()>3?Chat::chatEntries.size()-3:0;
        if(Chat::chatEntries.size()>0){
            for(int i=Chat::chatEntries.size()-1; i>=length; i--){
                if(!Chat::chatEntries[i].timedOut){
                    for(int a=0; a<Chat::chatEntries[i].textures.size(); a++){
                        SDL_QueryTexture(Chat::chatEntries[i].textures[a],0,0,&w2,&h2);
                        renderDraw(Chat::render,Chat::chatEntries[i].textures[a],Chat::x,Chat::posy);
                    }
                    Chat::posy-=h2+2;
                }
            }
        }
    }
    Chat::posy=y+Chat::h-20;
    if(Chat::enteringMessage){
        for(int i=Chat::chatEntries.size()-1; i>=Chat::messageOffset; i--){
            for(int a=0; a<Chat::chatEntries[i].textures.size(); a++){
                SDL_QueryTexture(Chat::chatEntries[i].textures[a],0,0,&w2,&h2);
                renderDraw(Chat::render,Chat::chatEntries[i].textures[a],Chat::x,Chat::posy);
            }
            Chat::posy-=h2+2;
        }
        guiRect.x=Chat::x;
        guiRect.y=400;
        guiRect.w=Chat::w;
        guiRect.h=30;
        SDL_SetRenderDrawColor(Chat::render,100,100,100,230);
        SDL_RenderFillRect(Chat::render,&guiRect);
        SDL_QueryTexture(Chat::messageTexture,0,0,&guiRect.w,&guiRect.h);
        SDL_RenderCopy(Chat::render,Chat::messageTexture,0,&guiRect);
    }
}
void Chat::addEntry(std::string str){
    Chat::chatEntries.push_back({str,SDL_GetTicks(),false});
    SDL_Surface* surf=TTF_RenderText_Blended(Chat::font,str.c_str(),{0,0,0});
    Chat::chatEntries.back().textures.push_back(SDL_CreateTextureFromSurface(Chat::render,surf));
    SDL_FreeSurface(surf);
}
void Chat::update(SDL_Event* ev){
    if(ev->type==SDL_TEXTINPUT && Chat::enteringMessage && !Chat::textfieldOpened && Chat::messageBuffer.size()<50){
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
            SDL_SetRelativeMouseMode(SDL_FALSE);
            SDL_CaptureMouse(SDL_FALSE);
        }
    }
    if(ev->type==SDL_KEYDOWN && Chat::enteringMessage){
        if(ev->key.keysym.scancode==SDL_SCANCODE_RETURN){
            if(Chat::messageBuffer.length()>0){
                
                Chat::addEntry(app->getUsername()+": "+Chat::messageBuffer);
                Chat::app->getServerConnection()->sendChatMessage(Chat::messageBuffer);
                Chat::messageBuffer="";
                SDL_Surface* surf=TTF_RenderText_Blended(Chat::font," ",{0,0,0});
                SDL_DestroyTexture(Chat::messageTexture);
                Chat::messageTexture=SDL_CreateTextureFromSurface(Chat::render,surf);
                SDL_FreeSurface(surf);
            }
        }
        if(ev->key.keysym.scancode==SDL_SCANCODE_ESCAPE){
            Chat::messageBuffer="";
            Chat::enteringMessage=false;
            SDL_SetRelativeMouseMode(SDL_TRUE);
            SDL_CaptureMouse(SDL_TRUE);
        }
        if(ev->key.keysym.scancode==SDL_SCANCODE_BACKSPACE){
            if(Chat::messageBuffer.length()>0){
                Chat::messageBuffer.pop_back();
                SDL_DestroyTexture(Chat::messageTexture);
                SDL_Surface* surf;
                if(Chat::messageBuffer=="")
                    surf=TTF_RenderText_Blended(Chat::font," ",{0,0,0});
                else
                    surf=TTF_RenderText_Blended(Chat::font,Chat::messageBuffer.c_str(),{0,0,0});
                Chat::messageTexture=SDL_CreateTextureFromSurface(Chat::render,surf);
                SDL_FreeSurface(surf);
            }
        }
    }
    if(ev->type==SDL_MOUSEWHEEL){
        if(Chat::enteringMessage && Chat::isMouseOn(ev->motion.x,ev->motion.y)){
            Chat::messageOffset+=ev->wheel.y;
            std::cout<<ev->wheel.y<<std::endl;
        }
    }
    
}
void Chat::updateEntries(){
    for(int i=0; i<Chat::chatEntries.size(); i++){
        if(Chat::chatEntries[i].sendTime+10000<=SDL_GetTicks()){
            // for(int a=0; a<Chat::chatEntries[i].textures.size(); a++)
            //     SDL_DestroyTexture(Chat::chatEntries[i].textures[a]);
            //Chat::chatEntries.erase(Chat::chatEntries.begin()+i);
            Chat::chatEntries[i].timedOut=true;
        }
    }
}
void Chat::setEnteringMessage(bool enteringMessage){
    Chat::enteringMessage=enteringMessage;
}
bool Chat::isEnteringMessage(){
    return Chat::enteringMessage;
}