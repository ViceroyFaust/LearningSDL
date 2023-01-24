#include "globals.h"

// The window of the application
SDL_Window* gWindow = nullptr;
// The renderer for the window
SDL_Renderer* gRenderer = nullptr;

// The background image
OwlTexture gBackgroundTexture;

// The music that will be played
Mix_Music *gMusic = nullptr;

// The sound effects that will be used
Mix_Chunk *gWilhelm = nullptr;
Mix_Chunk *gMinecraftOof = nullptr;
Mix_Chunk *gMinecraftCave = nullptr;
Mix_Chunk *gRobloxOof = nullptr;

