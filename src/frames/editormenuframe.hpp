#ifndef SRC_FRAMES_EDITORMENUFRAME_HPP
#define SRC_FRAMES_EDITORMENUFRAME_HPP
#include "../framework/frame.hpp"
#include "../SDL2_gui/SDLGui.h"
class EditorMenuFrame : public Frame{
    GUILabel* menuInfo;
	GUITextbox* mapName;
	GUIButton* edit;
public:
    void begin();
    void render();
    void finish();
};
#endif