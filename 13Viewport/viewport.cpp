#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const std::string SCREEN_TITLE = "Viewports Galore";

// The program window
SDL_Window* gWindow = nullptr;
// The window renderer
SDL_Renderer* gRenderer = nullptr;
// The displayed texture
SDL_Texture* gViewportTexture = nullptr;

// Initializes SDL. Returns true if succeeded, false if not
bool init() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Video Initialization Error: " << SDL_GetError() << "\n";
        return false;
    }

    // Create the window
    gWindow = SDL_CreateWindow(SCREEN_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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

    // Set color for renderer drawing operations
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xff);

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
    newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedImage);
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
    gViewportTexture = loadTexture("viewport.png");
    if (!gViewportTexture)
        return false;

    return true;
}

// Clean memory before exiting the program
void clean() {
    // Free Texture
    SDL_DestroyTexture(gViewportTexture);
    gViewportTexture = nullptr;
    // Destroy Window Renderer
    SDL_DestroyRenderer(gRenderer);
    gRenderer = nullptr;
    // Destroy the window
    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;

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

        // Top Left Viewport
        SDL_Rect topLeftViewport = {0, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
        SDL_RenderSetViewport(gRenderer, &topLeftViewport);
        SDL_RenderCopy(gRenderer, gViewportTexture, NULL, NULL);

        // Top Right Viewport
        SDL_Rect topRightViewport = {SCREEN_WIDTH / 2, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
        SDL_RenderSetViewport(gRenderer, &topRightViewport);
        SDL_RenderCopy(gRenderer, gViewportTexture, NULL, NULL);

        // Bottom Viewport
        SDL_Rect bottomViewport = {0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2};
        SDL_RenderSetViewport(gRenderer, &bottomViewport);
        SDL_RenderCopy(gRenderer, gViewportTexture, NULL, NULL);

        // Present the render
        SDL_RenderPresent(gRenderer);
        // Prevent the program from hogging the CPU by slowing down the loop
        SDL_Delay(33);
    }

    clean();

    return 0;
}
