#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

// Constants for the window
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const std::string SCREEN_TITLE = "Le Four Buttons";


// Button constants
const int BUTTON_WIDTH = 160;
const int BUTTON_HEIGHT = 120;
const int TOTAL_BUTTONS = 4;

enum OwlButtonSprite {
    BUTTON_SPRITE_MOUSE_OUT = 0,
    BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
    BUTTON_SPRITE_MOUSE_DOWN = 2,
    BUTTON_SPRITE_MOUSE_UP = 3,
    BUTTON_SPRITE_MOUSE_TOTAL = 4
};

#endif
