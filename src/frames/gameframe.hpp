#ifndef SRC_FRAMES_GAMEFRAME_HPP
#define SRC_FRAMES_GAMEFRAME_HPP
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
#include "../editor/editorerasetool.hpp"
#include "../time/timer.hpp"
#include "../world/skybox.hpp"
class GameFrame : public Frame{
    Ray* ray;
    World* world;
    Player* player;
    FPSCamera* cam;
    bool pause;
    GUIImage* crossair;
    Timer* updateTimer;
    Timer* activityTimer;
    Timer* positionTimer;
    Skybox* skybox;
public:
    void begin();
    void render();
    void finish();
};
#endif