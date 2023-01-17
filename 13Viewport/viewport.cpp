#include "constants.h"
#include "globals.h"
#include "util.h"
#include <SDL.h>

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
