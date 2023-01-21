#include "globals.h"


// The window of the application
SDL_Window* gWindow = nullptr;
// The renderer for the window
SDL_Renderer* gRenderer = nullptr;

// The buttons themselves
OwlButton gButtons[];

// Button clips and texture
SDL_Rect gSpriteClips[];
OwlTexture gButtonSpritesheet;

