#include <SDL2/SDL.h>
#include <iostream>

int main(int argc, char* argv[]) {
    SDL_Window *window = nullptr;

    // Initialize SDL. Quit early if an error is encountered
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Video Initialization Error: " << SDL_GetError() << "\n";
        return -1;
    }

    window = SDL_CreateWindow("Hello World!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        640, 480, SDL_WINDOW_SHOWN);
    // Quit early if an error is encountered during window creation
    if (!window) {
        std::cout << "Window Creation Error: " << SDL_GetError() << "\n";
        return -1;
    }

    // Show window for 3 seconds
    SDL_UpdateWindowSurface(window);
    SDL_Delay(3000);
    
    // Deallocate memory and quit SDL
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
