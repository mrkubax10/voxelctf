#include "timer.hpp"
Timer::Timer(long interval){
    Timer::interval=interval;
}
void Timer::reset(){
    Timer::start=SDL_GetTicks();
}
bool Timer::update(){
    Timer::end=SDL_GetTicks();
    if(Timer::start+Timer::interval<=Timer::end){
        return true;
    }
    else
        return false;
}