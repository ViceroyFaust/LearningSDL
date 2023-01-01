#include <SDL2/SDL.h>
#include <iostream>

int main(int argc, char *argv[]) {
    // Creating window variables
    SDL_Window *window = nullptr;
    SDL_Surface *windowSurface = nullptr;
    SDL_Surface *image1 = nullptr;
    SDL_Surface *image2 = nullptr;
    SDL_Surface *image3 = nullptr;
    SDL_Surface *currentImage = nullptr;

    // Initialize SDL. Quit early if an error is encountered
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Video Initialization Error: " << SDL_GetError() << "\n";
        return -1;
    }

    window = SDL_CreateWindow("Switch Me", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        640, 480, SDL_WINDOW_SHOWN);
    // Quit early if an error is encountered during window creation
    if (!window) {
        std::cout << "Window Creation Error: " << SDL_GetError() << "\n";
        return -1;
    }

    windowSurface = SDL_GetWindowSurface(window);

    image1 = SDL_LoadBMP("Image1.bmp");
    if (!image1) {
        std::cout << "Image Load Error: " << SDL_GetError() << "\n";
        SDL_DestroyWindow(window);
        return -1;
    }
    image2 = SDL_LoadBMP("Image2.bmp");
    if (!image2) {
        std::cout << "Image Load Error: " << SDL_GetError() << "\n";
        SDL_FreeSurface(image1);
        SDL_DestroyWindow(window);
        return -1;
    }
    image3 = SDL_LoadBMP("Image3.bmp");
    if (!image3) {
        std::cout << "Image Load Error: " << SDL_GetError() << "\n";
        SDL_FreeSurface(image2);
        SDL_FreeSurface(image1);
        SDL_DestroyWindow(window);
        return -1;
    }
    currentImage = image1;

    // Primary loop run flag
    bool isRunning = true;
    // Event handler
    SDL_Event ev;

    // Primary loop
    while (isRunning) {
        // Event loop
        while (SDL_PollEvent(&ev) != 0) {
            // Quit button detection
            if (ev.type == SDL_QUIT) {
                isRunning = false;
            }
            if (ev.type == SDL_KEYDOWN) {
                switch (ev.key.keysym.sym) {
                    case SDLK_1: 
                        currentImage = image1;
                        break;
                    case SDLK_2:
                        currentImage = image2;
                        break;
                    case SDLK_3:
                        currentImage = image3;
                        break;
                }
            }
        }

        SDL_BlitSurface(currentImage, NULL, windowSurface, NULL);
        SDL_UpdateWindowSurface(window);
        // Prevent the program from hogging the CPU by slowing down the loop
        SDL_Delay(33);
    }

    // Deallocate memory and quit SDL
    SDL_FreeSurface(image3);
    SDL_FreeSurface(image2);
    SDL_FreeSurface(image1);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
