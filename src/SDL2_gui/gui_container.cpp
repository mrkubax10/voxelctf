/*
 * gui_container.cpp
 *
 *  Created on: 9 lut 2020
 *      Author: kuba
 */

#include "gui_container.h"

GUIContainer::GUIContainer() {
	

}
void GUIContainer::setX(int x){
	GUIContainer::x=x;
	for(int i=0; i<GUIContainer::components.size(); i++){
		GUIContainer::components[i]->setX(x+GUIContainer::componentOriginalPositions[i].x);
	}
}
void GUIContainer::setY(int y){
	GUIContainer::y=y;
	for(int i=0; i<GUIContainer::components.size(); i++){
		GUIContainer::components[i]->setY(y+GUIContainer::componentOriginalPositions[i].y);
	}
}
void GUIContainer::center(int containerW,int containerH,bool vertically,bool horizontally){
	GUIContainer::x=(containerW-GUIComponent::w)/2;
	GUIContainer::y=(containerH-GUIComponent::h)/2;
	for(int i=0; i<GUIContainer::components.size(); i++){
		if(horizontally)
			GUIContainer::components[i]->setX(GUIContainer::x+GUIContainer::componentOriginalPositions[i].x);
		if(vertically)
			GUIContainer::components[i]->setY(GUIContainer::y+GUIContainer::componentOriginalPositions[i].y);
	}
}