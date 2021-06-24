#ifndef SRC_FRAMES_GAMEFRAME_HPP
#define SRC_FRAMES_GAMEFRAME_HPP
#include "../framework/frame.hpp"
#include "../maths/ray.hpp"
#include "../world/world.hpp"
#include "../gameplay/player.hpp"
#include "../editor/editortool.hpp"
#include "../editor/gui_blockinfo.hpp"
#include "../editor/gui_toolinfo.hpp"
#include "../render/fpscamera.hpp"
#include "../editor/editorfilltool.hpp"
#include "../editor/editorbuildtool.hpp"
#include "../editor/editorerasetool.hpp"
#include "../time/timer.hpp"
#include "../world/skybox.hpp"
#include "../gui/gui_image.hpp"
#include "../gui/gui_button.hpp"
#include "../maths/aabb.hpp"
#include "../gameplay/hud.hpp"
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
    GUIButton* buttonExit;
    GUIButton* buttonReturn;
    Model* playerModel;
    Model* flagModel;
    HUD* hud;
    long timeStart,timeEnd;
public:
    void begin();
    void render();
    void finish();
};
#endif