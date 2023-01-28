#include "util.h"
#include "constants.h"
#include "globals.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>

// Initializes SDL. Returns true if succeeded, false if not
bool init() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL Initialization Error: " << SDL_GetError() << "\n";
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
    // Load the font
    gFont = TTF_OpenFont("FiraCode-Regular.ttf", 24);
    if (!gFont) {
        std::cout << "Failed to load Fira Code font!\n";
        return false;
    }
    // Black colour for text
    SDL_Color textColor = {0, 0, 0, 255};

    if (!gPromptTexture.loadFromRenderedText("Press Enter to Reset Start Time.", textColor)) {
        std::cout << "Unable to render prompt\n";
        return false;
    }
    return true;
}

// Clean memory before exiting the program
void clean() {
    // Free Textures
    gPromptTexture.free()
    gTimeTextTexture.free()
    // Free the font
    TTF_CloseFont(gFont);
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

