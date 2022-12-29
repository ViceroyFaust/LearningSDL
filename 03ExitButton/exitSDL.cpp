#include <SDL2/SDL.h>
#include <iostream>

int main(int argc, char *argv[]) {
    // Creating window variables
    SDL_Window *window = nullptr;

    // Initialize SDL. Quit early if an error is encountered
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Video Initialization Error: " << SDL_GetError() << "\n";
        return -1;
    }

    window = SDL_CreateWindow("Exit Me", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        640, 480, SDL_WINDOW_SHOWN);
    // Quit early if an error is encountered during window creation
    if (!window) {
        std::cout << "Window Creation Error: " << SDL_GetError() << "\n";
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

        SDL_UpdateWindowSurface(window);
        // Prevent the program from hogging the CPU by slowing down the loop
        SDL_Delay(33);
    }

    // Deallocate memory and quit SDL
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
