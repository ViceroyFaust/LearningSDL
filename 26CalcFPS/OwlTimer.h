#ifndef OWLTIMER_H
#define OWLTIMER_H

#include <SDL.h>

class OwlTimer {
private:
    // Clock time when the timer started
    Uint32 mStartTicks;

    // The ticks when the timer paused
    Uint32 mPausedTicks;

    // Timer status
    bool mPaused;
    bool mStarted;

public:
    OwlTimer();

    // Timer actions
    void start();
    void stop();
    void pause();
    void unpause();

    // Get the timer's value
    Uint32 getTicks();

    // Get timer status
    bool isPaused();
    bool isStarted();
};

#endif
