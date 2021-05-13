#ifndef GUI_EFFECT_TRANSITION_H_INCLUDED
#define GUI_EFFECT_TRANSITION_H_INCLUDED
enum GUIEffectTransitionStartEvent{
    ON_CREATE,ON_HOVER,ON_CLICK
};
class GUIEffectTransition{
protected:
    GUIEffectTransitionStartEvent startEvent;
    int elementX,elementY,elementAdditional1,elementAdditional2,elementAdditional3,elementAdditional4;
public:
    GUIEffectTransition(GUIEffectTransitionStartEvent startEvent);
    virtual void update()=0;
    int getX();
    int getY();
};
class GUIEffectTransitionNone:public GUIEffectTransition{
    void update(){}
};
class GUIEffectTransitionSlide:public GUIEffectTransition{
    int speedX,speedY;
public:
    GUIEffectTransitionSlide(GUIEffectTransitionStartEvent startEvent,int speedX,int speedY):GUIEffectTransition(startEvent){GUIEffectTransitionSlide::speedX=speedX;
    GUIEffectTransitionSlide::speedY=speedY;}
    void update();

};

#endif // GUI_EFFECT_TRANSITION_H_INCLUDED
