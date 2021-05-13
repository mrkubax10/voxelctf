#include "textureatlas.hpp"
#include <GL/glew.h>
#include <GL/gl.h>
TextureAtlas::TextureAtlas(Renderer* renderer){
    TextureAtlas::renderer=renderer;
    TextureAtlas::renderTexture=new RenderTexture(TextureAtlas::maxTextureSize,textureSize);
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
    TextureAtlas::renderTexture->use();
    glClearColor(0,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT);
    int temp=0;
    for(int i=0; i<textureData.size(); i++){
        if(textureData[i][0]=='[' && textureData[i][textureData[i].length()-1]==']'){
            currentBlockID=(BlockType)std::stoi(textureData[i].substr(1,textureData[i].length()-1));
        }else{
            if(split(textureData[i],'=')[0]=="right"){
                renderer->drawTexturedRect(man->getNativeTexture("blocks/"+split(split(textureData[i],'=')[1],'.')[0]),glm::vec2(0,temp),glm::vec2(TextureAtlas::maxTextureSize,TextureAtlas::maxTextureSize));
                TextureAtlas::blockUVs[currentBlockID].right=(float)temp/(float)textureSize;
            }
            
            else if(split(textureData[i],'=')[0]=="left"){
                renderer->drawTexturedRect(man->getNativeTexture("blocks/"+split(split(textureData[i],'=')[1],'.')[0]),glm::vec2(0,temp),glm::vec2(TextureAtlas::maxTextureSize,TextureAtlas::maxTextureSize));
                TextureAtlas::blockUVs[currentBlockID].left=(float)temp/(float)textureSize;
            }
            else if(split(textureData[i],'=')[0]=="top"){
                renderer->drawTexturedRect(man->getNativeTexture("blocks/"+split(split(textureData[i],'=')[1],'.')[0]),glm::vec2(0,temp),glm::vec2(TextureAtlas::maxTextureSize,TextureAtlas::maxTextureSize));
                TextureAtlas::blockUVs[currentBlockID].top=(float)temp/(float)textureSize;
            }
            
            else if(split(textureData[i],'=')[0]=="bottom"){
                renderer->drawTexturedRect(man->getNativeTexture("blocks/"+split(split(textureData[i],'=')[1],'.')[0]),glm::vec2(0,temp),glm::vec2(TextureAtlas::maxTextureSize,TextureAtlas::maxTextureSize));
                TextureAtlas::blockUVs[currentBlockID].bottom=(float)temp/(float)textureSize;
            }
            else if(split(textureData[i],'=')[0]=="front"){
                renderer->drawTexturedRect(man->getNativeTexture("blocks/"+split(split(textureData[i],'=')[1],'.')[0]),glm::vec2(0,temp),glm::vec2(TextureAtlas::maxTextureSize,TextureAtlas::maxTextureSize));
                TextureAtlas::blockUVs[currentBlockID].front=(float)temp/(float)textureSize;
            }
            else if(split(textureData[i],'=')[0]=="all"){
                renderer->drawTexturedRect(man->getNativeTexture("blocks/"+split(split(textureData[i],'=')[1],'.')[0]),glm::vec2(0,temp),glm::vec2(TextureAtlas::maxTextureSize,TextureAtlas::maxTextureSize));
                TextureAtlas::blockUVs[currentBlockID].right=(float)temp/(float)textureSize;
                TextureAtlas::blockUVs[currentBlockID].left=(float)temp/(float)textureSize;
                TextureAtlas::blockUVs[currentBlockID].bottom=(float)temp/(float)textureSize;
                TextureAtlas::blockUVs[currentBlockID].top=(float)temp/(float)textureSize;
                TextureAtlas::blockUVs[currentBlockID].back=(float)temp/(float)textureSize;
                TextureAtlas::blockUVs[currentBlockID].front=(float)temp/(float)textureSize;
            }
            else if(split(textureData[i],'=')[0]=="side"){
                renderer->drawTexturedRect(man->getNativeTexture("blocks/"+split(split(textureData[i],'=')[1],'.')[0]),glm::vec2(0,temp),glm::vec2(TextureAtlas::maxTextureSize,TextureAtlas::maxTextureSize));
                TextureAtlas::blockUVs[currentBlockID].right=(float)temp/(float)textureSize;
                TextureAtlas::blockUVs[currentBlockID].left=(float)temp/(float)textureSize;
                TextureAtlas::blockUVs[currentBlockID].back=(float)temp/(float)textureSize;
                TextureAtlas::blockUVs[currentBlockID].front=(float)temp/(float)textureSize;
            }
            else if(split(textureData[i],'=')[0]=="back"){
                renderer->drawTexturedRect(man->getNativeTexture("blocks/"+split(split(textureData[i],'=')[1],'.')[0]),glm::vec2(0,temp),glm::vec2(TextureAtlas::maxTextureSize,TextureAtlas::maxTextureSize));
                TextureAtlas::blockUVs[currentBlockID].back=(float)temp/(float)textureSize;
            }
            temp+=TextureAtlas::maxTextureSize;
        }
    }
    TextureAtlas::renderTexture->useDefault();
    
    TextureAtlas::textureBlockSize=(float)TextureAtlas::maxTextureSize/(float)TextureAtlas::textureSize;
}
TextureAtlasBlockUV TextureAtlas::getBlockUV(uint8_t type){
    return TextureAtlas::blockUVs[(BlockType)type];
}
void TextureAtlas::use(){
    TextureAtlas::renderTexture->getTexture()->use();
}
float TextureAtlas::getTextureBlockSize(){
    return TextureAtlas::textureBlockSize;
}