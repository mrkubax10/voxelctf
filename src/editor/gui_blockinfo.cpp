#include "gui_blockinfo.hpp"
GUIBlockInfo::GUIBlockInfo(int x,int y,TTF_Font* font,Renderer* renderer){
    GUIBlockInfo::x=x;
    GUIBlockInfo::y=y;
    GUIBlockInfo::font=font;
    GUIBlockInfo::renderer=renderer;
    GUIBlockInfo::currentBlockId=BlockType::AIR;
    GUIBlockInfo::textureBlockName=new Texture();
    SDL_Surface* surf=TTF_RenderUTF8_Blended(font,blockNames[GUIBlockInfo::currentBlockId].c_str(),{255,255,255});
    textureBlockName->loadFromSurface(surf);
    SDL_FreeSurface(surf);
    GUIBlockInfo::visible=true;
}
std::string blockNames[]={
    "Stone","Cobblestone","Stone Bricks","Grass","Bricks","Sand","Iron","Gold","Crystal","Water","Lava","Dirt","Glass",
    "Cardboard","Polished Stone","Wood","Planks","Leaves"
};
void GUIBlockInfo::update(SDL_Event* ev){
    if(ev->type==SDL_MOUSEWHEEL){
        if(GUIBlockInfo::currentBlockId>BlockType::AIR && ev->wheel.y<0){
            GUIBlockInfo::currentBlockId--;
            SDL_Surface* surf=TTF_RenderUTF8_Blended(font,blockNames[GUIBlockInfo::currentBlockId].c_str(),{255,255,255});
            textureBlockName->loadFromSurface(surf);
            SDL_FreeSurface(surf);
        }
        if(GUIBlockInfo::currentBlockId<255 && ev->wheel.y>0){
            GUIBlockInfo::currentBlockId++;
            SDL_Surface* surf=TTF_RenderUTF8_Blended(font,blockNames[GUIBlockInfo::currentBlockId].c_str(),{255,255,255});
            textureBlockName->loadFromSurface(surf);
            SDL_FreeSurface(surf);

        }
    }
}
void GUIBlockInfo::draw(){
    renderer->drawTexturedRect(textureBlockName,glm::vec2(x,y),glm::vec2(textureBlockName->getW(),textureBlockName->getH()));
}