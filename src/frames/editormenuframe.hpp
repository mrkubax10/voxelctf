#ifndef SRC_FRAMES_EDITORMENUFRAME_HPP
#define SRC_FRAMES_EDITORMENUFRAME_HPP
#include "../framework/frame.hpp"
#include "../gui/gui_button.hpp"
#include "../gui/gui_label.hpp"
#include "../gui/gui_textbox.hpp"
class EditorMenuFrame : public Frame{
    GUILabel* menuInfo;
	GUITextbox* mapName;
	GUIButton* edit;
    GUIButton* buttonBack;
public:
    void begin();
    void render();
    void finish();
};
#endif