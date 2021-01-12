#include "editorfilltool.hpp"
void EditorFillTool::update(World* world,Player* player,Ray* ray,Uint8 button,BlockType blockType,TextureAtlas* textureAtlas){
    if(button==SDL_BUTTON_LEFT)
        EditorFillTool::fillPosition[0]=player->getPosition();
    if(button==SDL_BUTTON_RIGHT){
        std::vector<glm::vec2>* chunksToUpdate=new std::vector<glm::vec2>;
        EditorFillTool::fillPosition[1]=player->getPosition();
        
        for(int x=EditorFillTool::fillPosition[0].x; x<=EditorFillTool::fillPosition[1].x; x++){
            for(int y=EditorFillTool::fillPosition[0].y; y<=EditorFillTool::fillPosition[1].y; y++){
                for(int zz=EditorFillTool::fillPosition[0].z; zz<=EditorFillTool::fillPosition[1].z; zz++){
                    world->setBlock(x,y,zz,blockType);
                    std::cout<<x<<" "<<y<<" "<<zz<<std::endl;
                    if(!Chunk::findChunkInVector(*chunksToUpdate,glm::vec2(x/CHUNK_SIZE_WD,zz/CHUNK_SIZE_WD))){
                        chunksToUpdate->push_back(glm::vec2(x/CHUNK_SIZE_WD,zz/CHUNK_SIZE_WD));
                    }
                }
            }
        }
        
        for(int i=0; i<chunksToUpdate->size(); i++){
            world->getChunk((*chunksToUpdate)[i].x,(*chunksToUpdate)[i].y)->generateMesh(textureAtlas);
        }
        delete chunksToUpdate;
    }
}