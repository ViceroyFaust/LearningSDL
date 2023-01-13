#include <SDL2/SDL.h>
#include <iostream>

enum KeyPressImages {
    KEY_DEFAULT,
    KEY_ONE,
    KEY_TWO,
    KEY_THREE,
    KEY_TOTAL
};

SDL_Window* window = nullptr;
SDL_Surface* windowSurface = nullptr;

SDL_Surface* images[KEY_TOTAL];

SDL_Surface* currentImage = nullptr;

// Initializes SDL. Returns true if succeeded, false if not
bool init() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Video Initialization Error: " << SDL_GetError() << "\n";
        return false;
    }

    // Create the window
    window = SDL_CreateWindow("Press 1, 2, or 3!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        640, 480, SDL_WINDOW_SHOWN);
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
    SDL_Surface* loadedImage = SDL_LoadBMP(path.c_str());
    if (!loadedImage)
        std::cout << "Failed to load image " << path << " : " << SDL_GetError() << "\n";

    return loadedImage;
}

// Load pictures, etc. Returns true if succeeded, false if not
bool loadMedia() {
    images[KEY_DEFAULT] = loadImage("DefaultImage.bmp");
    if (!images[KEY_DEFAULT])
        return false;

    images[KEY_ONE] = loadImage("Image1.bmp");
    if (!images[KEY_ONE])
        return false;

    images[KEY_TWO] = loadImage("Image2.bmp");
    if (!images[KEY_TWO])
        return false;

    images[KEY_THREE] = loadImage("Image3.bmp");
    if (!images[KEY_THREE])
        return false;

    return true;
}

// Clean memory before exiting the program
void clean() {
    for (int i = 0; i < KEY_TOTAL; ++i) {
        SDL_FreeSurface(images[i]);
        images[i] = nullptr;
    }
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

    // Set the default image as current
    currentImage = images[KEY_DEFAULT];

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
                        currentImage = images[KEY_ONE];
                        break;
                    case SDLK_2:
                        currentImage = images[KEY_TWO];
                        break;
                    case SDLK_3:
                        currentImage = images[KEY_THREE];
                        break;
                    default:
                        currentImage = images[KEY_DEFAULT];
                }
            }
        }

        SDL_BlitSurface(currentImage, NULL, windowSurface, NULL);
        SDL_UpdateWindowSurface(window);
        // Prevent the program from hogging the CPU by slowing down the loop
        SDL_Delay(33);
    }

    clean();

    return 0;
}
