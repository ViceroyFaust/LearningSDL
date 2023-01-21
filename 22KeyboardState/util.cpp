#include "util.h"
#include "constants.h"
#include "globals.h"
#include <SDL_image.h>
#include <iostream>

// Initializes SDL. Returns true if succeeded, false if not
bool init() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Video Initialization Error: " << SDL_GetError() << "\n";
        return false;
    }

    // Create the window
    gWindow = SDL_CreateWindow(SCREEN_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    // Check if window has been created properly
    if (!gWindow) {
        std::cout << "Window Creation Error: " << SDL_GetError() << "\n";
        return false;
    }

    // Create a randerer for window
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    // Check if renderer has been created
    if (!gRenderer) {
        std::cout << "Renderer Creation Error: " << SDL_GetError() << "\n";
        return false;
    }

    // Set color for renderer drawing operations
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xff);

    // Initialize the PNG loading library
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        std::cout << "Image Library Creation Error: " << IMG_GetError() << "\n";
        return false;
    }

    #if defined(SDL_TTF_MAJOR_VERSION)
    // Initialize the TTF library
    if (TTF_Init() == -1) {
        std::cout << "TTF Library Creation Error: " << TTF_GetError() << "\n";
        return false;
    }
    #endif

    return true;
        
}

// Load pictures, etc. Returns true if succeeded, false if not
bool loadMedia() {
    if (!gDefaultTexture.loadFromFile("default.png")) {
        std::cout << "Failed to load default texture!\n";
        return false;
    }
    if (!gLeftTexture.loadFromFile("left.png")) {
        std::cout << "Failed to load left texture!\n";
        return false;
    }
    if (!gRightTexture.loadFromFile("right.png")) {
        std::cout << "Failed to load right texture!\n";
        return false;
    }
    if (!gUpTexture.loadFromFile("up.png")) {
        std::cout << "Failed to load up texture!\n";
        return false;
    }
    if (!gDownTexture.loadFromFile("down.png")) {
        std::cout << "Failed to load down texture!\n";
        return false;
    }

    return true;
}

// Clean memory before exiting the program
void clean() {
    // Free Textures
    gDefaultTexture.free();
    gLeftTexture.free();
    gRightTexture.free();
    gUpTexture.free();
    gDownTexture.free();
    // Destroy Window Renderer
    SDL_DestroyRenderer(gRenderer);
    gRenderer = nullptr;
    // Destroy the window
    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;

    // Quit SDL subsystems
    #if defined(SDL_TTF_MAJOR_VERSION)
    TTF_Quit();
    #endif
    IMG_Quit();
    SDL_Quit();
}

