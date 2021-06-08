#include "chat.hpp"
#include "../framework/app.hpp"
Chat::Chat(int x,int y,Renderer* renderer,TTF_Font* font,App* app){
    Chat::x=x;
    Chat::y=y;
    Chat::renderer=renderer;
    Chat::w=400;
    Chat::h=390;
    Chat::posy=0;
    Chat::font=font;
    Chat::enteringMessage=false;
    Chat::app=app;
    SDL_Surface* surf=TTF_RenderText_Blended(font," ",{0,0,0});
    Chat::messageTexture=new Texture();
    Chat::messageTexture->loadFromSurface(surf);
    SDL_FreeSurface(surf);
    Chat::textfieldOpened=false;
    Chat::messageBuffer="";
    Chat::visible=true;
    Chat::chatTexture=new RenderTexture(Chat::w,17*40);
}
void Chat::draw(){
    
    Chat::posy=3*15+10;
    if(!Chat::enteringMessage){
        int length=Chat::chatEntries.size()>3?Chat::chatEntries.size()-3:0;
        if(Chat::chatEntries.size()>0){
            for(int i=Chat::chatEntries.size()-1; i>=length; i--){
                if(!Chat::chatEntries[i].timedOut){
                    for(int a=0; a<Chat::chatEntries[i].textures.size(); a++){
                        renderer->drawTexturedRect(Chat::chatEntries[i].textures[a],glm::vec2(Chat::x,Chat::posy),glm::vec2(chatEntries[i].textures[a]->getW(),chatEntries[i].textures[a]->getH()));
                    }
                    Chat::posy-=h2+2;
                }
            }
        }
    }
    Chat::posy=Chat::h-20;
    if(Chat::enteringMessage){
        Chat::chatTexture->use();
        renderer->drawColoredRect(glm::vec4(100.0f/255.0f,100.0f/255.0f,100.0f/255.0f,1),glm::vec2(0,0),glm::vec2(Chat::w,17*40));
        for(int i=Chat::chatEntries.size()-1; i>=0; i--){
            for(int a=0; a<Chat::chatEntries[i].textures.size(); a++){
                renderer->drawTexturedRect(chatEntries[i].textures[a],glm::vec2(Chat::x,Chat::posy),glm::vec2(chatEntries[i].textures[a]->getW(),chatEntries[i].textures[a]->getH()));
            }
            Chat::posy-=h2+2;
        }
        RenderTexture::useDefault(app->getWindowW(),app->getWindowH());
        // guiRect.x=Chat::x;
        // guiRect.y=Chat::y;
        // guiRect.w=Chat::w;
        // guiRect.h=Chat::h;
        rect.x=0;
        rect.y=-Chat::messageOffset;
        rect.w=Chat::w;
        rect.h=Chat::h;
        renderer->drawTexturedRect(chatTexture->getTexture(),glm::vec2(Chat::x,Chat::y),glm::vec2(chatTexture->getW(),chatTexture->getH()));
        // guiRect.x=Chat::x;
        // guiRect.y=400;
        // guiRect.w=Chat::w;
        // guiRect.h=30;
        renderer->drawColoredRect(glm::vec4(100.0f/255.0f,100.0f/255.0f,100.0f/255.0f,1),glm::vec2(Chat::x,400),glm::vec2(Chat::w,30));
        renderer->drawTexturedRect(Chat::messageTexture,glm::vec2(Chat::x,400),glm::vec2(messageTexture->getW(),messageTexture->getH()));
    }
}
void Chat::addEntry(std::string str){
    Chat::chatEntries.push_back({str,SDL_GetTicks(),false});
    SDL_Surface* surf=TTF_RenderText_Blended(Chat::font,str.c_str(),{0,0,0});
    Texture* texture=new Texture();
    texture->loadFromSurface(surf);
    Chat::chatEntries.back().textures.push_back(texture);
    SDL_FreeSurface(surf);
}
void Chat::update(SDL_Event* ev){
    if(ev->type==SDL_TEXTINPUT && Chat::enteringMessage && !Chat::textfieldOpened && Chat::messageBuffer.size()<50){
        Chat::messageBuffer+=ev->text.text;
        SDL_Surface* surf=TTF_RenderText_Blended(Chat::font,Chat::messageBuffer.c_str(),{0,0,0});
        Chat::messageTexture->loadFromSurface(surf);
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
                Chat::messageTexture->loadFromSurface(surf);
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
                SDL_Surface* surf;
                if(Chat::messageBuffer=="")
                    surf=TTF_RenderText_Blended(Chat::font," ",{0,0,0});
                else
                    surf=TTF_RenderText_Blended(Chat::font,Chat::messageBuffer.c_str(),{0,0,0});
                Chat::messageTexture->loadFromSurface(surf);
                SDL_FreeSurface(surf);
            }
        }
    }
    // if(ev->type==SDL_MOUSEWHEEL){
    //     if(Chat::enteringMessage && Chat::isMouseOn(Chat::app->getMouseX(),Chat::app->getMouseY())){
    //         Chat::messageOffset+=ev->wheel.y;
    //     }
    // }
    
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