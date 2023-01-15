#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const std::string SCREEN_TITLE = "I render PNGs with Hardware";

// The program window
SDL_Window* window = nullptr;
// The window renderer
SDL_Renderer* renderer = nullptr;
// The displayed texture
SDL_Texture* texture = nullptr;

// Initializes SDL. Returns true if succeeded, false if not
bool init() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Video Initialization Error: " << SDL_GetError() << "\n";
        return false;
    }

    // Create the window
    window = SDL_CreateWindow(SCREEN_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    // Check if window has been created properly
    if (!window) {
        std::cout << "Window Creation Error: " << SDL_GetError() << "\n";
        return false;
    }

    // Create a randerer for window
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    // Check if renderer has been created
    if (!renderer) {
        std::cout << "Renderer Creation Error: " << SDL_GetError() << "\n";
        return false;
    }

    // Set color for renderer drawing operations
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xff);

    // Initialize the PNG loading library
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        std::cout << "Image Library Creation Error: " << IMG_GetError() << "\n";
        return false;
    }



    return true;
        
}

SDL_Texture* loadTexture(std::string path) {
    // Final texture, to return
    SDL_Texture* newTexture = nullptr;
    // Load image from path to surface
    SDL_Surface* loadedImage = IMG_Load(path.c_str());
    if (!loadedImage) {
        std::cout << "Failed to load image " << path << ": " << SDL_GetError() << "\n";
        return nullptr;
    }
   
    // Create a texture from surface
    newTexture = SDL_CreateTextureFromSurface(renderer, loadedImage);
    if (!newTexture) {
        std::cout << "Surface to Texture Conversion Error,"
            << path << ": " << SDL_GetError() << "\n";
        return nullptr;
    }
    // Free memory for unused loadedImage
    SDL_FreeSurface(loadedImage);

    return newTexture;
}

// Load pictures, etc. Returns true if succeeded, false if not
bool loadMedia() {
    texture = loadTexture("texture.png");
    if (!texture)
        return false;

    return true;
}

// Clean memory before exiting the program
void clean() {
    // Free Texture
    SDL_DestroyTexture(texture);
    texture = nullptr;
    // Destroy Window Renderer
    SDL_DestroyRenderer(renderer);
    renderer = nullptr;
    // Destroy the window
    SDL_DestroyWindow(window);
    window = nullptr;

    // Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char *argv[]) {
    if(!init()) {
        clean();
        return -1;
    }
    if (!loadMedia()) {
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
            if (ev.type == SDL_QUIT) {
                isRunning = false;
            }
        }

        // Clear screen
        SDL_RenderClear(renderer);
        // Render texture to screen
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        // Update Screen
        SDL_RenderPresent(renderer);
        // Prevent the program from hogging the CPU by slowing down the loop
        SDL_Delay(33);
    }

    clean();

    return 0;
}
