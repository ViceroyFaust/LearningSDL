#ifndef UTIL_H
#define UTIL_H

#include <SDL.h>

// Initialize SDL and create window
bool init();

// Load textures and other media needed
bool loadMedia();

// Clean memory up and exit SDL
void clean();

#endif
