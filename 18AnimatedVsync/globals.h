#ifndef GLOBALS_H
#define GLOBALS_H

#include <SDL.h>
#include "constants.h"
#include "OwlTexture.h"

// The window of the application
extern SDL_Window* gWindow;
// The renderer for the window
extern SDL_Renderer* gRenderer;

// Rectangle for clips and spritesheet texture
extern SDL_Rect gSpriteClips[WALKING_ANIMATION_FRAMES];
extern OwlTexture gSpriteSheetTexture;
#endif
