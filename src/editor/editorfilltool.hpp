#ifndef SRC_EDITOR_EDITORFILLTOOL_HPP
#define SRC_EDITOR_EDITORFILLTOOL_HPP
#include "editortool.hpp"
class EditorFillTool : public EditorTool{
    glm::vec3 fillPosition[2];
public:
    void update(World* world,Player* player,Ray* ray,Uint8 button,BlockType blockType,TextureAtlas* textureAtlas);
};
#endif