#include "editorerasetool.hpp"
void EditorEraseTool::update(World* world,Player* player,Ray* ray,Uint8 button,BlockType blockType,TextureAtlas* textureAtlas){
    if(button==SDL_BUTTON_LEFT)
        EditorEraseTool::fillPosition[0]=player->getPosition();
    if(button==SDL_BUTTON_RIGHT){
        std::vector<glm::vec2>* chunksToUpdate=new std::vector<glm::vec2>;
        EditorEraseTool::fillPosition[1]=player->getPosition();
        glm::vec3 tempPosition;
        if(EditorEraseTool::fillPosition[0].x>EditorEraseTool::fillPosition[1].x){
            tempPosition=EditorEraseTool::fillPosition[0];
            EditorEraseTool::fillPosition[0].x=EditorEraseTool::fillPosition[1].x;
            EditorEraseTool::fillPosition[1].x=tempPosition.x;
        }
        if(EditorEraseTool::fillPosition[0].y>EditorEraseTool::fillPosition[1].y){
            tempPosition=EditorEraseTool::fillPosition[0];
            EditorEraseTool::fillPosition[0].y=EditorEraseTool::fillPosition[1].y;
            EditorEraseTool::fillPosition[1].y=tempPosition.y;
        }
        if(EditorEraseTool::fillPosition[0].z>EditorEraseTool::fillPosition[1].z){
            tempPosition=EditorEraseTool::fillPosition[0];
            EditorEraseTool::fillPosition[0].z=EditorEraseTool::fillPosition[1].z;
            EditorEraseTool::fillPosition[1].z=tempPosition.z;
        }
        for(int x=EditorEraseTool::fillPosition[0].x; x<=EditorEraseTool::fillPosition[1].x; x++){
            for(int y=EditorEraseTool::fillPosition[0].y; y<=EditorEraseTool::fillPosition[1].y; y++){
                for(int zz=EditorEraseTool::fillPosition[0].z; zz<=EditorEraseTool::fillPosition[1].z; zz++){
                    world->setBlock(x,y,zz,BlockType::AIR);
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