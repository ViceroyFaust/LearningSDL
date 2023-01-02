#include <SDL2/SDL.h>
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
    // Creating window variables
    SDL_Window *window = nullptr;

    // Initialize SDL. Quit early if an error is encountered
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Video Initialization Error: " << SDL_GetError() << "\n";
        return -1;
    }

    window = SDL_CreateWindow("Texting", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
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

    // Get ready text input
    std::string text = "";
    SDL_StartTextInput();

    // Primary loop
    while (isRunning) {
        // Event loop
        while (SDL_PollEvent(&ev) != 0) {
            // Quit button detection
            if (ev.type == SDL_QUIT) 
                isRunning = false;
            if (ev.type == SDL_TEXTINPUT) {
                text += ev.text.text;
                system("clear");
                std::cout << text << "\n";
            }
            if (ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_BACKSPACE && text.length() > 0) {
                text = text.substr(0, text.length() - 1);
                system("clear");
                std::cout << text << "\n";
            }
        }

        SDL_UpdateWindowSurface(window);
        // Prevent the program from hogging the CPU by slowing down the loop
        SDL_Delay(33);
    }

    SDL_StopTextInput();

    // Deallocate memory and quit SDL
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
