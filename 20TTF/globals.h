#ifndef GLOBALS_H
#define GLOBALS_H

#include <SDL.h>
#include <SDL_ttf.h>
#include "constants.h"
#include "OwlTexture.h"

// The window of the application
extern SDL_Window* gWindow;
// The renderer for the window
extern SDL_Renderer* gRenderer;

// Global font
extern TTF_Font* gFont;

// Rendered Texture
extern OwlTexture gTextTexture;

#endif
