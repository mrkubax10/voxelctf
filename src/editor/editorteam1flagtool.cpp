#include "editorteam1flagtool.hpp"
void EditorTeam1FlagTool::update(World* world,Player* player,Ray* ray,Uint8 button,BlockType blockType,TextureAtlas* atlas){
    if(button==SDL_BUTTON_RIGHT){
        world->metadata.team1FlagPosition=ray->cast(world,player->getPosition(),false);
    }
}