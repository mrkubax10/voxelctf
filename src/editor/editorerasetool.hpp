#ifndef SRC_EDITOR_EDITORERASETOOL_HPP
#define SRC_EDITOR_EDITORERASETOOL_HPP
#include "editortool.hpp"
#include <glm/glm.hpp>
class EditorEraseTool : public EditorTool{
    glm::vec3 fillPosition[2];
public:
    void update(World* world,Player* player,Ray* ray,Uint8 button,BlockType blockType,TextureAtlas* textureAtlas);
};
#endif