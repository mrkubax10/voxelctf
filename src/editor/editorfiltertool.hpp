#ifndef SRC_EDITOR_EDITORFILTERTOOL_HPP
#define SRC_EDITOR_EDITORFILTERTOOL_HPP
#include "editortool.hpp"
class EditorFilterTool : public EditorTool{
    glm::vec3 fillPosition[2];
public:
    void update(World* world,Player* player,Ray* ray,Uint8 button,BlockType blockType,TextureAtlas* textureAtlas);
};
#endif