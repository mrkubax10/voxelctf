#include "gui_textbox.h"
GUITextbox::GUITextbox(int x,int y,int w,int h,TTF_Font *font,SDL_Renderer *render,std::string startText,int r,int g,int b){
    GUITextbox::x=x;
    GUITextbox::y=y;
    GUITextbox::w=w;
    GUITextbox::h=h;
    GUITextbox::buffer=startText;
    GUITextbox::render=render;
    GUITextbox::textureBuffer=SDL_CreateTextureFromSurface(render,TTF_RenderUTF8_Blended(font,startText.c_str(),{255,255,255}));
    GUITextbox::font=font;
    GUITextbox::selected=false;
    GUITextbox::active=false;
    GUITextbox::r=r;
    GUITextbox::g=g;
    GUITextbox::b=b;
}
void GUITextbox::draw(){
    guiRect.x=GUITextbox::x-2;
    guiRect.y=GUITextbox::y-2;
    guiRect.w=GUITextbox::w+4;
    guiRect.h=GUITextbox::h+4;
    if(GUITextbox::active || GUITextbox::selected){SDL_SetRenderDrawColor(GUITextbox::render,255,255,255,255);SDL_RenderFillRect(GUITextbox::render,&guiRect);}
    guiRect.x=GUITextbox::x;
    guiRect.y=GUITextbox::y;
    guiRect.w=GUITextbox::w;
    guiRect.h=GUITextbox::h;
    SDL_SetRenderDrawColor(GUITextbox::render,GUITextbox::r,GUITextbox::g,GUITextbox::b,255);
    SDL_RenderFillRect(GUITextbox::render,&guiRect);
    SDL_QueryTexture(GUITextbox::textureBuffer,0,0,&guiRect.w,&guiRect.h);
    guiRect.x=GUITextbox::x+(GUITextbox::w-guiRect.w)/2;
    guiRect.y=GUITextbox::y+(GUITextbox::h-guiRect.h)/2;
    SDL_RenderCopy(GUITextbox::render,GUITextbox::textureBuffer,0,&guiRect);
}
void GUITextbox::update(SDL_Event *ev){
    if(ev->type==SDL_MOUSEBUTTONDOWN){
        if(ev->motion.x>=GUITextbox::x && ev->motion.x<=GUITextbox::x+GUITextbox::w && ev->motion.y>=GUITextbox::y && ev->motion.y<=GUITextbox::y+GUITextbox::h) GUITextbox::active=true;
        else GUITextbox::active=false;
    }
    if(ev->type==SDL_TEXTINPUT){
        if(GUITextbox::active || GUITextbox::selected){
            SDL_QueryTexture(GUITextbox::textureBuffer,0,0,&guiRect.w,0);
            if(guiRect.w-1<GUITextbox::w){
                GUITextbox::buffer+=ev->text.text;
                SDL_DestroyTexture(GUITextbox::textureBuffer);
                GUITextbox::textureBuffer=SDL_CreateTextureFromSurface(GUITextbox::render,TTF_RenderUTF8_Blended(GUITextbox::font,GUITextbox::buffer.c_str(),{255,255,255}));
            }
        }
    }
    else if(ev->type==SDL_KEYDOWN){
        if(ev->key.keysym.sym==SDLK_BACKSPACE && (GUITextbox::active || GUITextbox::selected)){
            if(GUITextbox::buffer.length()>0){
                GUITextbox::buffer.pop_back();
                SDL_DestroyTexture(GUITextbox::textureBuffer);
                GUITextbox::textureBuffer=SDL_CreateTextureFromSurface(GUITextbox::render,TTF_RenderUTF8_Blended(GUITextbox::font,GUITextbox::buffer.c_str(),{255,255,255}));
            }
        }
    }
}
std::string GUITextbox::getText(){
	return buffer;
}
