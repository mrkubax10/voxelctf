#include "editorbuildtool.hpp"
void EditorBuildTool::update(World* world,Player* player,Ray* ray,Uint8 button,BlockType blockType,TextureAtlas* textureAtlas){
    if(button==SDL_BUTTON_LEFT){
        glm::vec3 pos=ray->cast(world,player->getPosition(),true);
        world->setBlock(player->getPosition().x+pos.x,player->getPosition().y+pos.y,player->getPosition().z+pos.z,BlockType::AIR);
        world->getChunk((player->getPosition().x+pos.x)/CHUNK_SIZE_WD,(player->getPosition().z+pos.z)/CHUNK_SIZE_WD)->generateMesh(textureAtlas);
    }
    else if(button==SDL_BUTTON_RIGHT){
        glm::vec3 pos=ray->cast(world,player->getPosition(),false);
        world->setBlock(player->getPosition().x+pos.x,player->getPosition().y+pos.y,player->getPosition().z+pos.z,blockType);
        world->getChunk((player->getPosition().x+pos.x)/CHUNK_SIZE_WD,(player->getPosition().z+pos.z)/CHUNK_SIZE_WD)->generateMesh(textureAtlas);
    }
}