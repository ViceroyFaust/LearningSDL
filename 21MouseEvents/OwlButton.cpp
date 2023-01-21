#include "OwlButton.h"
#include "globals.h"

OwlButton::OwlButton() : mPosition{0, 0}, mCurrentSprite(BUTTON_SPRITE_MOUSE_OUT)
{}

void OwlButton::setPosition(int x, int y) {
    mPosition.x = x;
    mPosition.y = y;
}

// Handles mouse events
void OwlButton::handleEvent(SDL_Event* e) {
    // If mouse event happened
    if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP) {
        int x, y;
        SDL_GetMouseState(&x, &y);

        // Check if the mouse is on the button
        bool onButton = true;
        if (x < mPosition.x || x > mPosition.x + BUTTON_WIDTH ||
                y < mPosition.y || y > mPosition.y + BUTTON_HEIGHT) {
            onButton = false;
        } 

        // Mouse is not on the button
        if (!onButton) {
            mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
            return;
        }
        // Set mouse over button sprite type
        switch (e->type) {
            case SDL_MOUSEMOTION:
                mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
                break;
            case SDL_MOUSEBUTTONDOWN:
                mCurrentSprite = BUTTON_SPRITE_MOUSE_DOWN;
                break;
            case SDL_MOUSEBUTTONUP:
                mCurrentSprite = BUTTON_SPRITE_MOUSE_UP;
        }
    }
}

// Show the button sprite
void OwlButton::render() {
    gButtonSpritesheet.render(mPosition.x, mPosition.y, &gSpriteClips[mCurrentSprite]);
}
