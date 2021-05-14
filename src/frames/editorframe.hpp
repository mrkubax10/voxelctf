#ifndef SRC_FRAMES_EDITORFRAME_HPP
#define SRC_FRAMES_EDITORFRAME_HPP
#include "../framework/frame.hpp"
#include "../maths/ray.hpp"
#include "../world/world.hpp"
#include "../gameplay/player.hpp"
#include "../editor/editortool.hpp"
#include "../gui/gui_button.hpp"
#include "../gui/gui_image.hpp"
#include "../gui/gui_label.hpp"
#include "../editor/gui_blockinfo.hpp"
#include "../editor/gui_toolinfo.hpp"
#include "../render/fpscamera.hpp"
#include "../editor/editorfilltool.hpp"
#include "../editor/editorbuildtool.hpp"
#include "../editor/editorerasetool.hpp"
#include "../editor/editorteam1flagtool.hpp"

#include "../editor/editorteam2flagtool.hpp"
#include "../time/timer.hpp"
#include "../world/skybox.hpp"
class EditorFrame : public Frame{
    Ray* ray;
    World* world;
    Player* player;
    FPSCamera* cam;
    bool pause;
    EditorTool* editorTool;
    GUIImage* crossair;
	GUIBlockInfo* blockInfo;
	GUIButton* buttonReturn;
	GUIButton* buttonSave;
	GUIButton* buttonSaveAndExit;
	GUIToolInfo* toolInfo;
	GUILabel* positionInfo;
    uint8_t blockType;
    Timer* updateTimer;
    Skybox* skybox;
    Model* flagModel;
    bool renderFlags;
    void createEmptyMap();
public:
    void begin();
    void render();
    void finish();
};
#endif