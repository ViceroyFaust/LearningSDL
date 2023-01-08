#include <SDL2/SDL.h>
#include <iostream>

SDL_Surface *optimizedSurface(std::string filePath, SDL_Surface *windowSurface) {
    SDL_Surface *optimizedSurface = nullptr;
    SDL_Surface *surface = SDL_LoadBMP(filePath.c_str());

    if (!surface) {
        std::cout << "Surface optimization Error: null windowSurface\n";
        return nullptr;
    }

    optimizedSurface = SDL_ConvertSurface(surface, windowSurface->format, 0);

    if (!optimizedSurface) {
        std::cout << "Surface optimization Error: conversion\n";
        return nullptr;
    }

    SDL_FreeSurface(surface);

    return optimizedSurface;
}

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

    window = SDL_CreateWindow("Exit Me", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        640, 480, SDL_WINDOW_SHOWN);
    // Quit early if an error is encountered during window creation
    if (!window) {
        std::cout << "Window Creation Error: " << SDL_GetError() << "\n";
        return -1;
    }

    // Get the window's surface and store it
    windowSurface = SDL_GetWindowSurface(window);
    // Load the BMP image
    imageSurface = optimizedSurface("image.bmp", windowSurface);

    // Check if image is loaded correctly. Exit early and cleanly if not
    if (!imageSurface) {
        std::cout << "Image Load Error: " << SDL_GetError() << "\n";
        SDL_FreeSurface(imageSurface);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }
    
    SDL_Rect drawingRect;
    drawingRect.x = 0;
    drawingRect.y = 0;
    drawingRect.w = 640;
    drawingRect.h = 480;

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

        // SDL_BlitSurface(imageSurface, NULL, windowSurface, NULL);
        SDL_BlitScaled(imageSurface, NULL, windowSurface, &drawingRect);
        SDL_UpdateWindowSurface(window);
        // Prevent the program from hogging the CPU by slowing down the loop
        SDL_Delay(33);
    }

    // Deallocate memory and quit SDL
    SDL_FreeSurface(imageSurface);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
