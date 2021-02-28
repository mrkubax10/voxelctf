#ifndef SRC_FRAMES_GAMEMENUFRAME_HPP
#define SRC_FRAMES_GAMEMENUFRAME_HPP
#include "../framework/frame.hpp"
#include "../SDL2_gui/SDLGui.h"
#include "../gameplay/gui_serverlist.hpp"
class GameMenuFrame : public Frame{
    GUITextbox* textboxIp;
	GUILabel* textboxIpInfo;
	GUITextbox* textboxName;
	GUILabel* textboxNameInfo;
	GUIButton* buttonPlay;
    GUIServerlist* serverlist;
    GUIButton* buttonAddServer;
    GUITextbox* textboxServerName;
    GUILabel* textboxServerNameInfo;
    std::vector<std::string> v1;
public:
    void begin();
    void render();
    void finish();
};
#endif