#include "editorteam2flagtool.hpp"
void EditorTeam2FlagTool::update(World* world,Player* player,Ray* ray,Uint8 button,BlockType blockType,TextureAtlas* atlas){
    if(button==SDL_BUTTON_RIGHT){
        world->metadata.team2FlagPosition=ray->cast(world,player->getPosition(),false);
    }
}