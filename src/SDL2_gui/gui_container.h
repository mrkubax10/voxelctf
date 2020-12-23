/*
 * gui_ontainer.h
 *
 *  Created on: 9 lut 2020
 *      Author: kuba
 */

#ifndef SRC_GUI_CONTAINER_H_
#define SRC_GUI_CONTAINER_H_
#include "gui_component.h"
#include <vector>
class GUIContainer:public GUIComponent {
protected:
	std::vector<GUIComponent*> components;
	std::vector<SDL_Point> componentOriginalPositions;
public:
	void setX(int x);
	void setY(int y);
	virtual void add(GUIComponent* component)=0;
	void center(int containerW,int containerH,bool vertically=true,bool horizontally=true);
	GUIContainer();
};

#endif /* SRC_GUI_CONTAINER_H_ */
