#include "gui_textbox.h"
#include "../framework/app.hpp"
GUITextbox::GUITextbox(int x,int y,int w,int h,Renderer* renderer,TTF_Font *font,std::string startText,int r,int g,int b){
    GUITextbox::x=x;
    GUITextbox::y=y;
    GUITextbox::w=w;
    GUITextbox::h=h;
    GUITextbox::buffer=startText;
    SDL_Surface* surf=TTF_RenderText_Blended(font,startText.c_str(),{255,255,255});
    GUITextbox::textureBuffer=new Texture();
    GUITextbox::textureBuffer->loadFromSurface(surf);
    SDL_FreeSurface(surf);
    GUITextbox::font=font;
    GUITextbox::selected=false;
    GUITextbox::active=false;
    GUITextbox::visible=true;
    GUITextbox::r=r;
    GUITextbox::g=g;
    GUITextbox::b=b;
    GUITextbox::renderer=renderer;
}
void GUITextbox::draw(){
    if(GUITextbox::active || GUITextbox::selected){
        renderer->drawColoredRect(glm::vec4(1,1,1,1),glm::vec2(x-1,y-1),glm::vec2(w+2,h+2));
        
    }
    renderer->drawColoredRect(glm::vec4(100.0f/255.0f,100.0f/255.0f,100.0f/255.0f,1),glm::vec2(x,y),glm::vec2(w,h));
    renderer->drawTexturedRect(GUITextbox::textureBuffer,glm::vec2(x,y),glm::vec2(textureBuffer->getW(),textureBuffer->getH()));
    if(GUITextbox::active || GUITextbox::selected){
        renderer->drawColoredRect(glm::vec4(1,1,1,1),glm::vec2(x+textureBuffer->getW()+1,y+1),glm::vec2(2,h-2));
    }
}
void GUITextbox::update(SDL_Event *ev){
    if(ev->type==SDL_MOUSEBUTTONDOWN){
        if(ev->motion.x>=GUITextbox::x && ev->motion.x<=GUITextbox::x+GUITextbox::w && ev->motion.y>=GUITextbox::y && ev->motion.y<=GUITextbox::y+GUITextbox::h) GUITextbox::active=true;
        else GUITextbox::active=false;
    }
    if(ev->type==SDL_TEXTINPUT){
        if(GUITextbox::active || GUITextbox::selected){
            if(textureBuffer->getW()-1<GUITextbox::w){
                GUITextbox::buffer+=ev->text.text;
                SDL_Surface* surf=TTF_RenderUTF8_Blended(GUITextbox::font,GUITextbox::buffer.c_str(),{255,255,255});
                textureBuffer->loadFromSurface(surf);
                SDL_FreeSurface(surf);
            }
        }
    }
    else if(ev->type==SDL_KEYDOWN){
        if(ev->key.keysym.sym==SDLK_BACKSPACE && (GUITextbox::active || GUITextbox::selected)){
            if(GUITextbox::buffer.length()>0){
                GUITextbox::buffer.pop_back();
                SDL_Surface* surf=TTF_RenderUTF8_Blended(GUITextbox::font,GUITextbox::buffer.c_str(),{255,255,255});
                textureBuffer->loadFromSurface(surf);
                SDL_FreeSurface(surf);
            }
        }
    }
}
std::string GUITextbox::getText(){
	return buffer;
}
void GUITextbox::setText(std::string text){
    SDL_Surface* surfText=TTF_RenderText_Blended(GUITextbox::font,text.c_str(),{255,255,255});
    textureBuffer->loadFromSurface(surfText);
    SDL_FreeSurface(surfText);
    GUITextbox::buffer=text;
}