#include "frame.hpp"
#include "app.hpp"
void Frame::setParent(App* parent){
    Frame::app=parent;
}

Frame::~Frame(){}