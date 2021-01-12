#ifndef SRC_EDITOR_EDITORTOOL_HPP
#define SRC_EDITOR_EDITORTOOL_HPP
#include "../world/world.hpp"
#include "../gameplay/player.hpp"
#include "../maths/ray.hpp"

#include "../world/textureatlas.hpp"
class EditorTool{
public:
    virtual void update(World* world,Player* player,Ray* ray,Uint8 button,BlockType blockType,TextureAtlas* textureAtlas)=0;
};
#endif