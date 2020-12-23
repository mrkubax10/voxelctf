#include "gui_blockinfo.hpp"
GUIBlockInfo::GUIBlockInfo(int x,int y,TTF_Font* font,SDL_Renderer* render){
    GUIBlockInfo::x=x;
    GUIBlockInfo::y=y;
    GUIBlockInfo::font=font;
    GUIBlockInfo::render=render;
    GUIBlockInfo::currentBlockId=BlockType::AIR;
    GUIBlockInfo::textureBlockName=SDL_CreateTextureFromSurface(render,TTF_RenderUTF8_Blended(font,blockNames[GUIBlockInfo::currentBlockId].c_str(),{255,255,255}));
}
std::string blockNames[]={
    "Stone","Cobblestone","Stone Bricks","Grass","Bricks","Sand","Iron","Gold","Crystal","Water","Lava","Dirt","Glass",
    "Cardboard"
};
void GUIBlockInfo::update(SDL_Event* ev){
    if(ev->type==SDL_MOUSEWHEEL){
        if(GUIBlockInfo::currentBlockId>BlockType::AIR && ev->wheel.y<0){
            GUIBlockInfo::currentBlockId--;
            SDL_DestroyTexture(GUIBlockInfo::textureBlockName);
            GUIBlockInfo::textureBlockName=SDL_CreateTextureFromSurface(GUIBlockInfo::render,TTF_RenderUTF8_Blended(font,blockNames[GUIBlockInfo::currentBlockId].c_str(),{255,255,255}));
        }
        if(GUIBlockInfo::currentBlockId<255 && ev->wheel.y>0){
            GUIBlockInfo::currentBlockId++;
            SDL_DestroyTexture(GUIBlockInfo::textureBlockName);
            GUIBlockInfo::textureBlockName=SDL_CreateTextureFromSurface(GUIBlockInfo::render,TTF_RenderUTF8_Blended(font,blockNames[GUIBlockInfo::currentBlockId].c_str(),{255,255,255}));

        }
    }
}
void GUIBlockInfo::draw(){
    guiRect.x=GUIBlockInfo::x;
    guiRect.y=GUIBlockInfo::y;
    SDL_QueryTexture(GUIBlockInfo::textureBlockName,0,0,&guiRect.w,&guiRect.h);
    SDL_RenderCopy(render,GUIBlockInfo::textureBlockName,0,&guiRect);
}