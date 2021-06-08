#include "textureatlas.hpp"
#include <GL/glew.h>
#include <GL/gl.h>
TextureAtlas::TextureAtlas(Renderer* renderer){
    TextureAtlas::renderer=renderer;
    TextureAtlas::texture=new Texture();
}
void TextureAtlas::generateTextureAtlas(ResourceManager* man){
    std::fstream file;
    file.open("res/textures/blocks/textureinfo",std::ios::in);
    std::string line;
    getline(file,line);
    TextureAtlas::maxTextureSize=std::stoi(line);
    BlockType currentBlockID;
    textureSize=0;
    std::vector<std::string> textureData;
    while(getline(file,line)){
        if(line[0]=='[' && line[line.length()-1]==']'){
            textureData.push_back(line);
        }else{
            textureData.push_back(line);
            textureSize+=TextureAtlas::maxTextureSize;
        }
    }
    file.close();
    TextureAtlas::surface=SDL_CreateRGBSurface(0,TextureAtlas::maxTextureSize,textureSize,32,0xff0000,0x00ff00,0x0000ff,0);
    SDL_FillRect(TextureAtlas::surface,0,SDL_MapRGB(TextureAtlas::surface->format,0,0,0));
    int temp=0;
    rect.x=0;
    rect.w=TextureAtlas::maxTextureSize;
    rect.h=TextureAtlas::maxTextureSize;
    for(int i=0; i<textureData.size(); i++){
        if(textureData[i][0]=='[' && textureData[i][textureData[i].length()-1]==']'){
            currentBlockID=(BlockType)std::stoi(textureData[i].substr(1,textureData[i].length()-1));
        }else{
            rect.y=temp;
            if(split(textureData[i],'=')[0]=="right"){
                SDL_BlitSurface(man->getSurface("blocks/"+split(split(textureData[i],'=')[1],'.')[0]),0,TextureAtlas::surface,&rect);
                TextureAtlas::blockUVs[currentBlockID].right=(float)temp/(float)textureSize;
            }
            
            else if(split(textureData[i],'=')[0]=="left"){
                SDL_BlitSurface(man->getSurface("blocks/"+split(split(textureData[i],'=')[1],'.')[0]),0,TextureAtlas::surface,&rect);
                TextureAtlas::blockUVs[currentBlockID].left=(float)temp/(float)textureSize;
            }
            else if(split(textureData[i],'=')[0]=="top"){
                SDL_BlitSurface(man->getSurface("blocks/"+split(split(textureData[i],'=')[1],'.')[0]),0,TextureAtlas::surface,&rect);
                TextureAtlas::blockUVs[currentBlockID].top=(float)temp/(float)textureSize;
            }
            
            else if(split(textureData[i],'=')[0]=="bottom"){
                SDL_BlitSurface(man->getSurface("blocks/"+split(split(textureData[i],'=')[1],'.')[0]),0,TextureAtlas::surface,&rect);
                TextureAtlas::blockUVs[currentBlockID].bottom=(float)temp/(float)textureSize;
            }
            else if(split(textureData[i],'=')[0]=="front"){
                SDL_BlitSurface(man->getSurface("blocks/"+split(split(textureData[i],'=')[1],'.')[0]),0,TextureAtlas::surface,&rect);
                TextureAtlas::blockUVs[currentBlockID].front=(float)temp/(float)textureSize;
            }
            else if(split(textureData[i],'=')[0]=="all"){
                SDL_BlitSurface(man->getSurface("blocks/"+split(split(textureData[i],'=')[1],'.')[0]),0,TextureAtlas::surface,&rect);
                TextureAtlas::blockUVs[currentBlockID].right=(float)temp/(float)textureSize;
                TextureAtlas::blockUVs[currentBlockID].left=(float)temp/(float)textureSize;
                TextureAtlas::blockUVs[currentBlockID].bottom=(float)temp/(float)textureSize;
                TextureAtlas::blockUVs[currentBlockID].top=(float)temp/(float)textureSize;
                TextureAtlas::blockUVs[currentBlockID].back=(float)temp/(float)textureSize;
                TextureAtlas::blockUVs[currentBlockID].front=(float)temp/(float)textureSize;
            }
            else if(split(textureData[i],'=')[0]=="side"){
                SDL_BlitSurface(man->getSurface("blocks/"+split(split(textureData[i],'=')[1],'.')[0]),0,TextureAtlas::surface,&rect);
                TextureAtlas::blockUVs[currentBlockID].right=(float)temp/(float)textureSize;
                TextureAtlas::blockUVs[currentBlockID].left=(float)temp/(float)textureSize;
                TextureAtlas::blockUVs[currentBlockID].back=(float)temp/(float)textureSize;
                TextureAtlas::blockUVs[currentBlockID].front=(float)temp/(float)textureSize;
            }
            else if(split(textureData[i],'=')[0]=="back"){
                SDL_BlitSurface(man->getSurface("blocks/"+split(split(textureData[i],'=')[1],'.')[0]),0,TextureAtlas::surface,&rect);
                TextureAtlas::blockUVs[currentBlockID].back=(float)temp/(float)textureSize;
            }
            temp+=TextureAtlas::maxTextureSize;
        }
    }
    TextureAtlas::textureBlockSize=(float)TextureAtlas::maxTextureSize/(float)TextureAtlas::textureSize;
    TextureAtlas::texture->loadFromSurface(TextureAtlas::surface);
    SDL_FreeSurface(TextureAtlas::surface);
}
TextureAtlasBlockUV TextureAtlas::getBlockUV(uint8_t type){
    return TextureAtlas::blockUVs[(BlockType)type];
}
void TextureAtlas::use(){
    TextureAtlas::texture->use();
}
float TextureAtlas::getTextureBlockSize(){
    return TextureAtlas::textureBlockSize;
}
Texture* TextureAtlas::getTexture(){
    return texture;
}