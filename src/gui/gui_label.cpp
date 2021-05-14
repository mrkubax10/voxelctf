/*
 * gui_label.cpp
 *
 *  Created on: 1 lut 2020
 *      Author: kubaz_000
 */

#include "gui_label.hpp"
GUILabel::GUILabel(int x,int y,std::string text,Renderer* renderer,TTF_Font* font,SDL_Color color,int alpha) {
	GUILabel::x=x;
	GUILabel::y=y;
	GUILabel::text=text;
	GUILabel::font=font;
	GUILabel::alpha=alpha;
	GUILabel::clicked=false;
	GUILabel::color=color;
	GUILabel::visible=true;
	GUILabel::textureText=new Texture();
	SDL_Surface* surf=TTF_RenderUTF8_Blended(font,text.c_str(),color);
	GUILabel::textureText->loadFromSurface(surf);
	GUILabel::w=surf->w;
	GUILabel::h=surf->h;
	SDL_FreeSurface(surf);
	GUILabel::renderer=renderer;
	
}
void GUILabel::update(SDL_Event *ev){
	if(ev->type==SDL_MOUSEBUTTONDOWN){
		if(ev->button.button==SDL_BUTTON_LEFT){
			if(ev->motion.x>=GUILabel::x && ev->motion.x<=GUILabel::x+GUILabel::w && ev->motion.y>=GUILabel::y && ev->motion.y<=GUILabel::y+GUILabel::h){
				GUILabel::clicked=1;
			}else{
				GUILabel::clicked=0;
			}
		}
	}else
		GUILabel::clicked=0;
	if(ev->type==SDL_MOUSEMOTION){
		if(!(ev->motion.x>=GUILabel::x && ev->motion.x<=GUILabel::x+GUILabel::w && ev->motion.y>=GUILabel::y && ev->motion.y<=GUILabel::y+GUILabel::h)){
			GUILabel::clicked=0;
		}
	}
}
void GUILabel::draw(){
	renderer->drawTexturedRect(textureText,glm::vec2(x,y),glm::vec2(textureText->getW(),textureText->getH()));
}
bool GUILabel::isClicked(){
	return GUILabel::clicked;
}
void GUILabel::setText(std::string text){
	SDL_Surface* textSurface=TTF_RenderUTF8_Blended(GUILabel::font,text.c_str(),GUILabel::color);
	GUILabel::textureText->loadFromSurface(textSurface);
	GUILabel::text=text;
	GUILabel::w=textSurface->w;
	GUILabel::h=textSurface->h;
	SDL_FreeSurface(textSurface);
}