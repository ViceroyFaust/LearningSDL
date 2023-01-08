#include <SDL2/SDL.h>
#include <iostream>

SDL_Texture *loadTexture(std::string filePath, SDL_Renderer *renderTarget) {
    SDL_Texture *texture = nullptr;
    SDL_Surface *surface = SDL_LoadBMP(filePath.c_str());

    if (!surface) {
        std::cout << "Picture Loading Error\n";
        return nullptr;
    }

    texture = SDL_CreateTextureFromSurface(renderTarget, surface);

    if (!texture) {
        std::cout << "Texture Creation Error\n";
        return nullptr;
    }

    SDL_FreeSurface(surface);

    return texture;
}

int main(int argc, char *argv[]) {
    // Creating window variables
    SDL_Window *window = nullptr;
    SDL_Renderer *renderTarget = nullptr;
    SDL_Texture *imageTexture = nullptr;

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
        SDL_Quit();
        return -1;
    }

    // -1 tells to use any compatible driver. SDL_RENDERER_ACCELERATED means
    // that this renderer will use the GPU
    renderTarget = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderTarget) {
        std::cout << "Renderer Activation Error: " << SDL_GetError() << "\n";
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    imageTexture = loadTexture("image.bmp", renderTarget);

    // Check if image is loaded correctly. Exit early and cleanly if not
    if (!imageTexture) {
        std::cout << "Image Load Error: " << SDL_GetError() << "\n";
        SDL_DestroyRenderer(renderTarget);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }
    
    // Primary loop run flag
    bool isRunning = true;
    // Event handler
    SDL_Event ev;

    SDL_RenderClear(renderTarget);
    SDL_RenderCopy(renderTarget, imageTexture, NULL, NULL);
    SDL_RenderPresent(renderTarget);
    // Primary loop
    while (isRunning) {
        // Event loop
        while (SDL_PollEvent(&ev) != 0) {
            // Quit button detection
            if(ev.type == SDL_QUIT)
                isRunning = false;
        }
        
        // Prevent the program from hogging the CPU by slowing down the loop
        SDL_Delay(33);
    }

    // Deallocate memory and quit SDL
    SDL_DestroyTexture(imageTexture);
    SDL_DestroyRenderer(renderTarget);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
