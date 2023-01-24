#ifndef GLOBALS_H
#define GLOBALS_H

#include <SDL.h>
#include <SDL_mixer.h>
#include "constants.h"
#include "OwlTexture.h"

// The window of the application
extern SDL_Window* gWindow;
// The renderer for the window
extern SDL_Renderer* gRenderer;

// The background image
extern OwlTexture gBackgroundTexture;

// The music that will be played
extern Mix_Music *gMusic;

// The sound effects that will be used
extern Mix_Chunk *gWilhelm;
extern Mix_Chunk *gMinecraftOof;
extern Mix_Chunk *gMinecraftCave;
extern Mix_Chunk *gRobloxOof;
#endif
