/*
 * gui_label.cpp
 *
 *  Created on: 1 lut 2020
 *      Author: kubaz_000
 */

#include "gui_label.h"

GUILabel::GUILabel(int x,int y,std::string text,TTF_Font* font,SDL_Color color,SDL_Renderer *render,int alpha) {
	GUILabel::x=x;
	GUILabel::y=y;
	GUILabel::text=text;
	GUILabel::font=font;
	GUILabel::render=render;
	GUILabel::alpha=alpha;
	GUILabel::clicked=false;
	GUILabel::color=color;
	SDL_Surface* textSurface=TTF_RenderUTF8_Blended(font,text.c_str(),color);
	GUILabel::visible=true;
	GUILabel::textureText=SDL_CreateTextureFromSurface(render,textSurface);
	SDL_SetTextureAlphaMod(GUILabel::textureText,alpha);
	SDL_QueryTexture(GUILabel::textureText,0,0,&w,&h);
	SDL_FreeSurface(textSurface);
	
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
	SDL_QueryTexture(GUILabel::textureText,0,0,&guiRect.w,&guiRect.h);
	guiRect.x=GUILabel::x;
	guiRect.y=GUILabel::y;
	SDL_RenderCopy(GUILabel::render,GUILabel::textureText,0,&guiRect);
}
bool GUILabel::isClicked(){
	return GUILabel::clicked;
}
void GUILabel::setText(std::string text){
	SDL_DestroyTexture(GUILabel::textureText);
	SDL_Surface* textSurface=TTF_RenderUTF8_Blended(GUILabel::font,text.c_str(),GUILabel::color);
	GUILabel::textureText=SDL_CreateTextureFromSurface(GUILabel::render,textSurface);
	GUILabel::text=text;
	SDL_QueryTexture(GUILabel::textureText,0,0,&w,&h);
	SDL_FreeSurface(textSurface);
}