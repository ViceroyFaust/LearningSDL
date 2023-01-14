#include <SDL2/SDL.h>
#include <iostream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const std::string SCREEN_TITLE = "I Am Stretch :3";

SDL_Window* window = nullptr;
SDL_Surface* windowSurface = nullptr;
SDL_Surface* image = nullptr;

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

    // Get the window's surface
    windowSurface = SDL_GetWindowSurface(window);

    return true;
        
}

SDL_Surface* loadImage(std::string path) {
    // Final, optimized surface to return
    SDL_Surface* optimizedSurface = nullptr;
    // Loaded surface
    SDL_Surface* loadedImage = SDL_LoadBMP(path.c_str());
    if (!loadedImage) {
        std::cout << "Failed to load image " << path << ": " << SDL_GetError() << "\n";
        return nullptr;
    }
    
    // Convert the loaded surface to screen format (flag must always be 0)
    optimizedSurface = SDL_ConvertSurface(loadedImage, windowSurface->format, 0);
    if (!optimizedSurface) {
        std::cout << "Failed to optimize image " << path << ": " << SDL_GetError() << "\n";
        return nullptr;
    }

    // Free the allocated memory
    SDL_FreeSurface(loadedImage);
    loadedImage = nullptr;

    return optimizedSurface;
}

// Load pictures, etc. Returns true if succeeded, false if not
bool loadMedia() {
    image = loadImage("gato.bmp");
    if (!image)
        return false;

    return true;
}

// Clean memory before exiting the program
void clean() {
    // Free the image memory
    SDL_FreeSurface(image);
    image = nullptr;
    // Destroy the window
    SDL_DestroyWindow(window);
    window = nullptr;

    // Quit SDL
    SDL_Quit();
}

int main(int argc, char *argv[]) {
    if(!init())
        return -1;

    if (!loadMedia()) {
        clean();
        return -1;
    }

    // Apply the stretched image via rect
    SDL_Rect stretchRect;
    stretchRect.x = 0;
    stretchRect.y = 0;
    stretchRect.w = SCREEN_WIDTH;
    stretchRect.h = SCREEN_HEIGHT;
    SDL_BlitScaled(image, NULL, windowSurface, &stretchRect);

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

        SDL_UpdateWindowSurface(window);
        // Prevent the program from hogging the CPU by slowing down the loop
        SDL_Delay(33);
    }

    clean();

    return 0;
}
