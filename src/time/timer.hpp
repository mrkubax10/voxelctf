#ifndef SRC_TIMER_HPP
#define SRC_TIMER_HPP
#include <SDL2/SDL.h>
class Timer{
    long start,end,interval;
public:
    Timer(long interval);
    void reset();
    bool update();
};
#endif