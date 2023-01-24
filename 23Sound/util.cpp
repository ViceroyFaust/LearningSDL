#include "util.h"
#include "constants.h"
#include "globals.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>

// Initializes SDL. Returns true if succeeded, false if not
bool init() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
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

    // Initializer SDL Mixer itself, with mp3 support
    int mixerFlags = MIX_INIT_MP3;
    if (!(Mix_Init(mixerFlags) & mixerFlags)) {
        std::cout << "SDL Mixer Initialization Error: " << Mix_GetError() << "\n";
        return false;
    }

    // Initialize SDL Mixer Audio Device
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024) < 0) {
        std::cout << "Audio Device Initialization Error: " << Mix_GetError() << "\n";
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
    // Load background image
    if(!gBackgroundTexture.loadFromFile("background.png")) {
        std::cout << "Failed to load background!\n";
        return false;
    }
    // Load music
    gMusic = Mix_LoadMUS("jazzBlue.mp3");
    if (!gMusic) {
        std::cout << "Failed to load music!\n";
        return false;
    }
    // Load the sound effects
    gWilhelm = Mix_LoadWAV("wilhelm.mp3");
    if (!gWilhelm) {
        std::cout << "Failed to load wilhelm!\n";
        return false;
    }

    gMinecraftOof = Mix_LoadWAV("minecraft_oof.mp3");
    if (!gMinecraftOof) {
        std::cout << "Failed to load Minecraft oof!\n";
        return false;
    }

    gMinecraftCave = Mix_LoadWAV("minecraft_cave.mp3");
    if (!gMinecraftCave) {
        std::cout << "Failed to load Minecraft cave!\n";
        return false;
    }

    gRobloxOof = Mix_LoadWAV("roblox_oof.mp3");
    if (!gRobloxOof) {
        std::cout << "Failed to load Roblox oof!\n";
        return false;
    }

    return true;
}

// Clean memory before exiting the program
void clean() {
    // Free Textures
    gBackgroundTexture.free();
    // Free music
    Mix_FreeMusic(gMusic);
    gMusic = nullptr;
    // Free the sound effects
    Mix_FreeChunk(gWilhelm);
    Mix_FreeChunk(gMinecraftOof);
    Mix_FreeChunk(gMinecraftCave);
    Mix_FreeChunk(gRobloxOof);
    gWilhelm = nullptr;
    gMinecraftOof = nullptr;
    gMinecraftCave = nullptr;
    gRobloxOof = nullptr;
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
    Mix_Quit();
    SDL_Quit();
}

