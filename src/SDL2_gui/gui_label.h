#ifndef GUI_LABEL_H_INCLUDED
#define GUI_LABEL_H_INCLUDED
#include "gui_global.h"
#include "gui_component.h"
#include <iostream>
class GUILabel:public GUIComponent {
	std::string text;
	SDL_Color color;
	int alpha;
	TTF_Font *font;
	bool clicked;
	SDL_Texture* textureText;
public:
	GUILabel(int x,int y,std::string text,TTF_Font* font,SDL_Color color,SDL_Renderer *render,int alpha=255);
	void update(SDL_Event *ev);
	void draw();
	bool isClicked();
	void setText(std::string text);
};
#endif // GUI_LABEL_H_INCLUDED

