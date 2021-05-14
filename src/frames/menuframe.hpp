#ifndef SRC_FRAMES_MENUFRAME_HPP
#define SRC_FRAMES_MENUFRAME_HPP
#include "../framework/frame.hpp"
#include "../gui/gui_button.hpp"
#include "../gui/gui_label.hpp"
#include "../gui/gui_image.hpp"
class MenuFrame : public Frame{
    // GUI
	GUIImage* imageLogo;
	GUIButton* buttonPlay;
	GUIButton* buttonFastGame;
	GUIButton* buttonEditor;
	GUIButton* buttonSettings;
	GUIButton* buttonAuthors;
	GUIButton* buttonExit;
	GUILabel* labelVersion;
	Texture* logoFull;
public:
    void begin();
    void render();
    void finish();
};
#endif