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

    // Angle of rotation for face
    double degrees = 0.0;

    // Flip type
    SDL_RendererFlip flipType = SDL_FLIP_NONE;

    // Primary loop
    while (isRunning) {
        // Event loop
        while (SDL_PollEvent(&ev) != 0) {
            // Quit button detection
            if (ev.type == SDL_QUIT) {
                isRunning = false;
            }
        }
        // Clear screen and draw background color
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);
        
        // render the face in the center
        int screenCenterX = (SCREEN_WIDTH - gTextTexture.getWidth()) / 2;
        int screenCenterY = (SCREEN_HEIGHT - gTextTexture.getHeight()) / 2;
        gTextTexture.render(screenCenterX, screenCenterY);

        // Update screen
        SDL_RenderPresent(gRenderer);
    }

    clean();

    return 0;
}
