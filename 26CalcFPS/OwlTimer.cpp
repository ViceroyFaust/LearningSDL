#include "OwlTimer.h"

OwlTimer::OwlTimer() : mStartTicks(0), mPausedTicks(0), mPaused(false), mStarted(false) {}

void OwlTimer::start() {
    // Start the timer
    mStarted = true;
    
    // Unpause the timer
    mPaused = false;

    // Get the current clock time
    mStartTicks = SDL_GetTicks();
    mPausedTicks = 0;
}

void OwlTimer::stop() {
    // Stop the timer
    mStarted = false;

    // Unpause the timer
    mPaused = false;
    
    // Clear tick variables
    mStartTicks = 0;
    mPausedTicks = 0;
}

void OwlTimer::pause() {
    // Do nothing if not started or already paused
    if (!mStarted || mPaused)
        return;
    
    // Pause the timer
    mPaused = true;
    
    // Calculate the paused ticks
    mPausedTicks = SDL_GetTicks() - mStartTicks;
    mStartTicks = 0;
}

void OwlTimer::unpause() {
    // Do nothing if the timer hasn't been started or isn't paused
    if (!mStarted || !mPaused)
        return;

    // Unpause the timer
    mPaused = false;

    // Reset the starting ticks
    mStartTicks = SDL_GetTicks() - mPausedTicks;

    // Reset the paused ticks
    mPausedTicks = 0;
}

Uint32 OwlTimer::getTicks() {
    // If the timer hasn't been started, no time passed
    if (!mStarted)
        return 0;
    // Return the ticks when the timer was paused
    if (mPaused)
        return mPausedTicks;
    // Return current time minus the start time if timer is started and unpaused
    return SDL_GetTicks() - mStartTicks;
}

bool OwlTimer::isPaused() {
    return mPaused;
}

bool OwlTimer::isStarted() {
    return mStarted;
}
