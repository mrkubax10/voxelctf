#ifndef SRC_FRAMES_EDITORFRAME_HPP
#define SRC_FRAMES_EDITORFRAME_HPP
#include "../framework/frame.hpp"
#include "../maths/ray.hpp"
#include "../world/world.hpp"
#include "../gameplay/player.hpp"
#include "../editor/editortool.hpp"
#include "../SDL2_gui/SDLGui.h"
#include "../editor/gui_blockinfo.hpp"
#include "../editor/gui_toolinfo.hpp"
#include "../render/fpscamera.hpp"
#include "../editor/editorfilltool.hpp"
#include "../editor/editorbuildtool.hpp"
#include "../time/timer.hpp"
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
public:
    void begin();
    void render();
    void finish();
};
#endif