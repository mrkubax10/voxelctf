#ifndef SRC_EDITOR_EDITORBUILDTOOL_HPP
#define SRC_EDITOR_EDITORBUILDTOOL_HPP
#include "editortool.hpp"
class EditorBuildTool : public EditorTool{
public:
    void update(World* world,Player* player,Ray* ray,Uint8 button,BlockType blockType,TextureAtlas* textureAtlas);
};
#endif