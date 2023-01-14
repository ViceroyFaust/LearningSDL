#include <SDL2/SDL.h>
#include <iostream>

// Window to which we will render
SDL_Window *window = nullptr;
// The surface contained by the window
SDL_Surface *windowSurface = nullptr;

// Initializes SDL. Returns true if succeeded, false if not
bool init() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Video Initialization Error: " << SDL_GetError() << "\n";
        return false;
    }

    // Create the window
    window = SDL_CreateWindow("Close Me!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
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

// Clean memory before exiting the program
void clean() {
    // Destroy the window
    SDL_DestroyWindow(window);
    window = nullptr;

    // Quit SDL
    SDL_Quit();
}

int main(int argc, char *argv[]) {
    bool initStatus = init();

    // Clean and exit if initialization fails
    if (!initStatus) {
        std::cout << "Initialization failed! Cleaning and exiting...\n";
        clean();
        return -1;
    }

    // Primary loop run flag
    bool isRunning = true;
    // Event handler
    SDL_Event ev;

    // Primary loop
    while (isRunning) {
        // Event loop
        while (SDL_PollEvent(&ev) != 0) {
            // Quit button detection
            if(ev.type == SDL_QUIT)
                isRunning = false;
        }
        // Make the window a certain colour
        SDL_FillRect(windowSurface, NULL, SDL_MapRGB(windowSurface->format, 0x38, 0xF0, 0xF9));
        // Make sure the changes are visible
        SDL_UpdateWindowSurface(window);

        // Prevent the program from hogging the CPU by slowing down the loop
        SDL_Delay(33);
    }

    clean();
    return 0;
}
