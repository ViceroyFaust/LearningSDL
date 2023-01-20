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

    // Current animation frame
    int frame = 0;

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

        // Render current frame
        SDL_Rect* currentClip = &gSpriteClips[frame / 5];
        gSpriteSheetTexture.render((SCREEN_WIDTH - currentClip->w) / 2, (SCREEN_HEIGHT - currentClip->h) / 2,
                currentClip);

        // Update screen
        SDL_RenderPresent(gRenderer);

        ++frame;
        if (frame / 5 >= WALKING_ANIMATION_FRAMES)
            frame = 0;
    }

    clean();

    return 0;
}
