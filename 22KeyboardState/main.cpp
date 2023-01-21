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

    OwlTexture* currentTexture = nullptr;
    // Primary loop
    while (isRunning) {
        // Event loop
        while (SDL_PollEvent(&ev) != 0) {
            // Quit button detection
            if (ev.type == SDL_QUIT) {
                isRunning = false;
            }

        }
        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
        if (currentKeyStates[SDL_SCANCODE_UP]) {
            currentTexture = &gUpTexture;
        } else if (currentKeyStates[SDL_SCANCODE_DOWN]) {
            currentTexture = &gDownTexture;
        } else if (currentKeyStates[SDL_SCANCODE_LEFT]) {
            currentTexture = &gLeftTexture;
        } else if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
            currentTexture = &gRightTexture;
        } else {
            currentTexture = &gDefaultTexture;
        }

        // Clear screen and draw background color
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);

        currentTexture->render(0, 0);

        // Update screen
        SDL_RenderPresent(gRenderer);
    }

    clean();

    return 0;
}
