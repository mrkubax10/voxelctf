#ifndef SRC_FRAMES_GAMEMENUFRAME_HPP
#define SRC_FRAMES_GAMEMENUFRAME_HPP
#include "../framework/frame.hpp"
#include "../SDL2_gui/SDLGui.h"
class GameMenuFrame : public Frame{
    GUITextbox* textboxIp;
	GUILabel* textboxIpInfo;
	GUITextbox* textboxName;
	GUILabel* textboxNameInfo;
	GUIButton* buttonPlay;
public:
    void begin();
    void render();
    void finish();
};
#endif