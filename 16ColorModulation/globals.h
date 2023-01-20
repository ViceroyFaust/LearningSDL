#ifndef GLOBALS_H
#define GLOBALS_H

#include <SDL.h>
#include "OwlTexture.h"

// The window of the application
extern SDL_Window* gWindow;
// The renderer for the window
extern SDL_Renderer* gRenderer;

// The photo to modulate
extern OwlTexture gPhoto;
#endif
