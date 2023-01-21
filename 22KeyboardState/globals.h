#ifndef GLOBALS_H
#define GLOBALS_H

#include <SDL.h>
#include "constants.h"
#include "OwlTexture.h"

// The window of the application
extern SDL_Window* gWindow;
// The renderer for the window
extern SDL_Renderer* gRenderer;

// The texture images
extern OwlTexture gDefaultTexture;
extern OwlTexture gLeftTexture;
extern OwlTexture gRightTexture;
extern OwlTexture gUpTexture;
extern OwlTexture gDownTexture;

#endif
