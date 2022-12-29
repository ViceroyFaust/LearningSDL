#include <SDL2/SDL.h>
#include <iostream>

int main(int argc, char *argv[]) {
    // Creating window variables
    SDL_Window *window = nullptr;
    SDL_Surface *windowSurface = nullptr;
    SDL_Surface *imageSurface = nullptr;

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

    // Get the window's surface and store it
    windowSurface = SDL_GetWindowSurface(window);
    // Load the BMP image
    imageSurface = SDL_LoadBMP("helloPicture.bmp");

    // Check if image is loaded correctly. Exit early and cleanly if not
    if (!imageSurface) {
        std::cout << "Image Load Error: " << SDL_GetError() << "\n";
        SDL_FreeSurface(imageSurface);
        SDL_FreeSurface(windowSurface);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // Show picture for 3 seconds on screen
    SDL_BlitSurface(imageSurface, NULL, windowSurface, NULL);
    SDL_UpdateWindowSurface(window);
    SDL_Delay(3000);
    
    // Deallocate memory and quit SDL
    SDL_FreeSurface(imageSurface);
    SDL_FreeSurface(windowSurface);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}