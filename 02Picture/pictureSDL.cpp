#include <SDL2/SDL.h>
#include <iostream>

// Window to which we will render
SDL_Window *window = nullptr;
// The surface contained by the window
SDL_Surface *windowSurface = nullptr;
// The image that will be loaded from disk
SDL_Surface *imageSurface = nullptr;

// Initializes SDL. Returns true if succeeded, false if not
bool init() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Video Initialization Error: " << SDL_GetError() << "\n";
        return false;
    }

    // Create the window
    window = SDL_CreateWindow("Hello World!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        640, 480, SDL_WINDOW_SHOWN);
    // Check if window has been created properly
    if (!window) {
        std::cout << "Window Creation Error: " << SDL_GetError() << "\n";
        return false;
    }

    // Get the window's surface
    windowSurface = SDL_GetWindowSurface(window);

    return true;
        
}

// Load pictures, etc. Returns true if succeeded, false if not
bool loadMedia() {
    imageSurface = SDL_LoadBMP("helloPicture.bmp");
    // Check if image is loaded correctly. Exit early and cleanly if not
    if (!imageSurface) {
        std::cout << "Image Load Error: " << SDL_GetError() << "\n";
        return false;
    }

    return true;
}

// Clean memory before exiting the program
void clean() {
    // Deallocate the image surface
    SDL_FreeSurface(imageSurface);
    imageSurface = nullptr;

    // Destroy the window
    SDL_DestroyWindow(window);
    window = nullptr;

    // Quit SDL
    SDL_Quit();
}

int main(int argc, char *argv[]) {
    bool initStatus = init();
    bool imageStatus = loadMedia();

    // Check if init failed. If so, clean and exit
    if (!initStatus || !imageStatus) {
        std::cout << "Initialization Failed! Cleaning and exiting...\n";
        clean();
        return -1;
    }
    // Show picture for 3 seconds on screen
    SDL_BlitSurface(imageSurface, NULL, windowSurface, NULL);
    SDL_UpdateWindowSurface(window);
    SDL_Delay(3000);
    
    return 0;
}
