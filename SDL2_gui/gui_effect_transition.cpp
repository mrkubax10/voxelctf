#include "gui_effect_transition.h"
int GUIEffectTransition::getX(){
    return GUIEffectTransition::elementX;
}
int GUIEffectTransition::getY(){
    return GUIEffectTransition::elementY;
}

void GUIEffectTransitionSlide::update(){
    GUIEffectTransitionSlide::elementX+=GUIEffectTransitionSlide::speedX;
    GUIEffectTransitionSlide::elementY+=GUIEffectTransitionSlide::speedY;
}
