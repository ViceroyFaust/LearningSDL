#ifndef OWLBUTTON_H
#define OWLBUTTON_H

#include <SDL.h>
#include "constants.h"

class OwlButton {
private:
    // Top left position
    SDL_Point mPosition;

    // Currently used global sprite
    OwlButtonSprite mCurrentSprite;
public:
    OwlButton();
    
    void setPosition(int x, int y);

    // Handles mouse events
    void handleEvent(SDL_Event* e);

    // Show the button sprite
    void render();
};

#endif
