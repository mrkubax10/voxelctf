#ifndef SRC_EDITOR_EDITORTEAM2FLAGTOOL_HPP
#define SRC_EDITOR_EDITORTEAM2FLAGTOOL_HPP
#include "editortool.hpp"
class EditorTeam2FlagTool : public EditorTool{
    void update(World* world,Player* player,Ray* ray,Uint8 button,BlockType blockType,TextureAtlas* atlas);
};
#endif