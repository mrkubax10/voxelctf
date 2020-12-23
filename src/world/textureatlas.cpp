#include "textureatlas.hpp"
TextureAtlas::TextureAtlas(SDL_Renderer* render){
    TextureAtlas::render=render;
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
    TextureAtlas::texture=SDL_CreateTexture(render,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,TextureAtlas::maxTextureSize,textureSize);
    SDL_SetRenderTarget(render,TextureAtlas::texture);
    int temp=0;
    for(int i=0; i<textureData.size(); i++){
        if(textureData[i][0]=='[' && textureData[i][textureData[i].length()-1]==']'){
            currentBlockID=(BlockType)std::stoi(textureData[i].substr(1,textureData[i].length()-1));
        }else{
            if(split(textureData[i],'=')[0]=="right"){
                renderDrawScaled(render,man->getTexture("blocks/"+split(split(textureData[i],'=')[1],'.')[0]),0,temp,TextureAtlas::maxTextureSize,TextureAtlas::maxTextureSize);
                TextureAtlas::blockUVs[currentBlockID].right=(float)temp/(float)textureSize;
            }
            
            else if(split(textureData[i],'=')[0]=="left"){
                renderDrawScaled(render,man->getTexture("blocks/"+split(split(textureData[i],'=')[1],'.')[0]),0,temp,TextureAtlas::maxTextureSize,TextureAtlas::maxTextureSize);
                TextureAtlas::blockUVs[currentBlockID].left=(float)temp/(float)textureSize;
            }
            else if(split(textureData[i],'=')[0]=="top"){
                renderDrawScaled(render,man->getTexture("blocks/"+split(split(textureData[i],'=')[1],'.')[0]),0,temp,TextureAtlas::maxTextureSize,TextureAtlas::maxTextureSize);
                TextureAtlas::blockUVs[currentBlockID].top=(float)temp/(float)textureSize;
            }
            
            else if(split(textureData[i],'=')[0]=="bottom"){
                renderDrawScaled(render,man->getTexture("blocks/"+split(split(textureData[i],'=')[1],'.')[0]),0,temp,TextureAtlas::maxTextureSize,TextureAtlas::maxTextureSize);
                TextureAtlas::blockUVs[currentBlockID].bottom=(float)temp/(float)textureSize;
            }
            else if(split(textureData[i],'=')[0]=="front"){
                renderDrawScaled(render,man->getTexture("blocks/"+split(split(textureData[i],'=')[1],'.')[0]),0,temp,TextureAtlas::maxTextureSize,TextureAtlas::maxTextureSize);
                TextureAtlas::blockUVs[currentBlockID].front=(float)temp/(float)textureSize;
            }
            else if(split(textureData[i],'=')[0]=="all"){
                renderDrawScaled(render,man->getTexture("blocks/"+split(split(textureData[i],'=')[1],'.')[0]),0,temp,TextureAtlas::maxTextureSize,TextureAtlas::maxTextureSize);
                TextureAtlas::blockUVs[currentBlockID].right=(float)temp/(float)textureSize;
                TextureAtlas::blockUVs[currentBlockID].left=(float)temp/(float)textureSize;
                TextureAtlas::blockUVs[currentBlockID].bottom=(float)temp/(float)textureSize;
                TextureAtlas::blockUVs[currentBlockID].top=(float)temp/(float)textureSize;
                TextureAtlas::blockUVs[currentBlockID].back=(float)temp/(float)textureSize;
                TextureAtlas::blockUVs[currentBlockID].front=(float)temp/(float)textureSize;
            }
            else if(split(textureData[i],'=')[0]=="side"){
                renderDrawScaled(render,man->getTexture("blocks/"+split(split(textureData[i],'=')[1],'.')[0]),0,temp,TextureAtlas::maxTextureSize,TextureAtlas::maxTextureSize);
                TextureAtlas::blockUVs[currentBlockID].right=(float)temp/(float)textureSize;
                TextureAtlas::blockUVs[currentBlockID].left=(float)temp/(float)textureSize;
                TextureAtlas::blockUVs[currentBlockID].back=(float)temp/(float)textureSize;
                TextureAtlas::blockUVs[currentBlockID].front=(float)temp/(float)textureSize;
            }
            else if(split(textureData[i],'=')[0]=="back"){
                renderDrawScaled(render,man->getTexture("blocks/"+split(split(textureData[i],'=')[1],'.')[0]),0,temp,TextureAtlas::maxTextureSize,TextureAtlas::maxTextureSize);
                TextureAtlas::blockUVs[currentBlockID].back=(float)temp/(float)textureSize;
            }
            temp+=TextureAtlas::maxTextureSize;
        }
    }
    SDL_SetRenderTarget(render,0);
    TextureAtlas::textureBlockSize=(float)TextureAtlas::maxTextureSize/(float)TextureAtlas::textureSize;
}
TextureAtlasBlockUV TextureAtlas::getBlockUV(uint8_t type){
    return TextureAtlas::blockUVs[(BlockType)type];
}
void TextureAtlas::use(){
    SDL_GL_BindTexture(TextureAtlas::texture,0,0);
}
float TextureAtlas::getTextureBlockSize(){
    return TextureAtlas::textureBlockSize;
}