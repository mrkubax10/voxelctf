#include "editorfiltertool.hpp"
void EditorFilterTool::update(World* world,Player* player,Ray* ray,Uint8 button,BlockType blockType,TextureAtlas* textureAtlas){
    if(button==SDL_BUTTON_LEFT)
        EditorFilterTool::fillPosition[0]=player->getPosition();
    if(button==SDL_BUTTON_RIGHT){
        std::vector<glm::vec2>* chunksToUpdate=new std::vector<glm::vec2>;
        EditorFilterTool::fillPosition[1]=player->getPosition();
        glm::vec3 tempPosition;
        if(EditorFilterTool::fillPosition[0].x>EditorFilterTool::fillPosition[1].x){
            tempPosition=EditorFilterTool::fillPosition[0];
            EditorFilterTool::fillPosition[0].x=EditorFilterTool::fillPosition[1].x;
            EditorFilterTool::fillPosition[1].x=tempPosition.x;
        }
        if(EditorFilterTool::fillPosition[0].y>EditorFilterTool::fillPosition[1].y){
            tempPosition=EditorFilterTool::fillPosition[0];
            EditorFilterTool::fillPosition[0].y=EditorFilterTool::fillPosition[1].y;
            EditorFilterTool::fillPosition[1].y=tempPosition.y;
        }
        if(EditorFilterTool::fillPosition[0].z>EditorFilterTool::fillPosition[1].z){
            tempPosition=EditorFilterTool::fillPosition[0];
            EditorFilterTool::fillPosition[0].z=EditorFilterTool::fillPosition[1].z;
            EditorFilterTool::fillPosition[1].z=tempPosition.z;
        }
        for(int x=EditorFilterTool::fillPosition[0].x; x<=EditorFilterTool::fillPosition[1].x; x++){
            for(int y=EditorFilterTool::fillPosition[0].y; y<=EditorFilterTool::fillPosition[1].y; y++){
                for(int zz=EditorFilterTool::fillPosition[0].z; zz<=EditorFilterTool::fillPosition[1].z; zz++){
                    world->setBlock(x,y,zz,blockType);
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