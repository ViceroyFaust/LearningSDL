#include <SDL2/SDL.h>
#include <iostream>
#include <string>

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
const std::string title = "Geometry";

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

    // Primary loop
    while (isRunning) {
        // Event loop
        while (SDL_PollEvent(&ev) != 0) {
            // Quit button detection
            if(ev.type == SDL_QUIT)
                isRunning = false;
        }

        // Draw a dark background
        SDL_SetRenderDrawColor(gRenderer, 0x2E, 0x34, 0x40, 0xFF);
        SDL_RenderClear(gRenderer);
        // Draw a red rectangle
        SDL_Rect fillRect = {WINDOW_WIDTH/4, WINDOW_HEIGHT/4, WINDOW_WIDTH/2, WINDOW_HEIGHT/2};
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
        SDL_RenderFillRect(gRenderer, &fillRect);
        // Draw a green outline rectangle
        SDL_Rect outlineRect = {WINDOW_WIDTH/6, WINDOW_HEIGHT/6, WINDOW_WIDTH * 2/3, WINDOW_HEIGHT * 2/3};
        SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
        SDL_RenderDrawRect(gRenderer, &outlineRect);
        // Draw a blue horizontal line
        SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xFF, 0xFF);
        SDL_RenderDrawLine(gRenderer, 0, WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT / 2);
        // Draw a yellow dotted line
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0x00, 0xFF);
        for (int i = 0; i < WINDOW_HEIGHT; i += 4) {
            SDL_RenderDrawPoint(gRenderer, WINDOW_WIDTH / 2, i);
        }
        // Update the screen
        SDL_RenderPresent(gRenderer);
        // Prevent the program from hogging the CPU by slowing down the loop
        SDL_Delay(33);
    }

    clean();
    return 0;
}
