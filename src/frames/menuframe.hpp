#ifndef SRC_FRAMES_MENUFRAME_HPP
#define SRC_FRAMES_MENUFRAME_HPP
#include "../framework/frame.hpp"
#include "../gui/gui_button.h"
#include "../gui/gui_label.h"
class MenuFrame : public Frame{
    // GUI
    GUILabel* labelLogo;
	GUIButton* buttonPlay;
	GUIButton* buttonFastGame;
	GUIButton* buttonEditor;
	GUIButton* buttonSettings;
	GUIButton* buttonAuthors;
	GUIButton* buttonExit;
	GUILabel* labelVersion;
public:
    void begin();
    void render();
    void finish();
};
#endif