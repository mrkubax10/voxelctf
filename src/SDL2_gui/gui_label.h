#ifndef GUI_LABEL_H_INCLUDED
#define GUI_LABEL_H_INCLUDED
#include "gui_global.h"
#include "gui_component.h"
#include <iostream>
#include "../render/texture.hpp"
#include "../render/shaderprogram.hpp"
class GUILabel:public GUIComponent {
	std::string text;
	SDL_Color color;
	int alpha;
	TTF_Font *font;
	bool clicked;
	Texture* textureText;
public:
	GUILabel(int x,int y,std::string text,Renderer* renderer,TTF_Font* font,SDL_Color color,int alpha=255);
	void update(SDL_Event *ev);
	void draw();
	bool isClicked();
	void setText(std::string text);
};
#endif // GUI_LABEL_H_INCLUDED

