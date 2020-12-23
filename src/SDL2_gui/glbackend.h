/*
 * glbackend.h
 *
 *  Created on: 16 kwi 2020
 *      Author: kuba
 */

#ifndef SRC_SDL2_GUI_GLBACKEND_H_
#define SRC_SDL2_GUI_GLBACKEND_H_
#define SDL2_GUI_GL_BACKEND
//Uncomment above if you want SDL2_gui GL backend.
#ifdef SDL2_GUI_GL_BACKEND

#include "../render/gl2drenderer.hpp"
#include "SDLGui.h"
namespace GUIGLBackend{
	SDL_Texture* guiTexture;
	void initTexture(int w,int h,SDL_Renderer* render);
	void drawGUI(GUIManager* man,SDL_Renderer* render,GL2DRenderer* gl2d);
}

#endif
#endif /* SRC_SDL2_GUI_GLBACKEND_H_ */
