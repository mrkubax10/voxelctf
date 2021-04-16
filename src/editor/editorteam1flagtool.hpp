#ifndef SRC_EDITOR_EDITORTEAM1FLAGTOOL_HPP
#define SRC_EDITOR_EDTIROTEAM1FLAGTOOL_HPP
#include "editortool.hpp"
class EditorTeam1FlagTool : public EditorTool{
    void update(World* world,Player* player,Ray* ray,Uint8 button,BlockType blockType,TextureAtlas* atlas);
};
#endif