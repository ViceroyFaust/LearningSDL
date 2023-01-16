#include <SDL2/SDL.h>
#include <iostream>
#include <string>

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
const std::string title = "Square that Moves";

// Window to which we will render
SDL_Window* gWindow = nullptr;
// Window's renderer
SDL_Renderer* gRenderer = nullptr;

// Initializes SDL. Returns true if succeeded, false if not
bool init() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Video Initialization Error: " << SDL_GetError() << "\n";
        return false;
    }

    // Create the window
    gWindow = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    // Check if window has been created properly
    if (!gWindow) {
        std::cout << "Window Creation Error: " << SDL_GetError() << "\n";
        return false;
    }

    // Create a randerer for window
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    // Check if renderer has been created
    if (!gRenderer) {
        std::cout << "Renderer Creation Error: " << SDL_GetError() << "\n";
        return false;
    }

    return true;
        
}

// Clean memory before exiting the program
void clean() {
    // Destroy the window
    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;

    // Quit SDL
    SDL_Quit();
}

int main(int argc, char *argv[]) {
    if (!init()) {
        clean();
        return -1;
    }

    // Primary loop run flag
    bool isRunning = true;
    // Event handler
    SDL_Event ev;
    
    // Rectange that follows the mouse
    SDL_Rect mouseSquare = {0, 0, 128, 128};

    // Primary loop
    while (isRunning) {
        // Event loop
        while (SDL_PollEvent(&ev) != 0) {
            // Quit button detection
            if(ev.type == SDL_QUIT) {
                isRunning = false;
            }
            if (ev.type == SDL_MOUSEMOTION) {
              mouseSquare.x = ev.button.x - 64;
              mouseSquare.y = ev.button.y - 64;
            }
        }

        // Draw a dark background
        SDL_SetRenderDrawColor(gRenderer, 0x2E, 0x34, 0x40, 0xFF);
        SDL_RenderClear(gRenderer);
        // Draw a red rectangle
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
        SDL_RenderFillRect(gRenderer, &mouseSquare);
        // Update the screen
        SDL_RenderPresent(gRenderer);
        // Prevent the program from hogging the CPU by slowing down the loop
        SDL_Delay(33);
    }

    clean();
    return 0;
}
