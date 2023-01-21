#ifndef GLOBALS_H
#define GLOBALS_H

#include <SDL.h>
#include "constants.h"
#include "OwlButton.h"
#include "OwlTexture.h"

// The window of the application
extern SDL_Window* gWindow;
// The renderer for the window
extern SDL_Renderer* gRenderer;

// The buttons themselves
extern OwlButton gButtons[4];

// Button clips and texture
extern SDL_Rect gSpriteClips[4];
extern OwlTexture gButtonSpritesheet;

#endif
