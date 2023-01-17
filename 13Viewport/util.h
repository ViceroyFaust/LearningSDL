#ifndef UTIL_H
#define UTIL_H

#include <SDL.h>
#include <string>

// Initialize SDL and create window
bool init();

SDL_Texture* loadTexture(std::string path);

// Load textures and other media needed
bool loadMedia();

// Clean memory up and exit SDL
void clean();

#endif
