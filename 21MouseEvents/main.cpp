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

    // Top left button
    gButtons[0].setPosition(0, 0);
    // Top right button
    gButtons[1].setPosition(SCREEN_WIDTH - BUTTON_WIDTH, 0);
    // Bottom left button
    gButtons[2].setPosition(0, SCREEN_HEIGHT - BUTTON_HEIGHT);
    // Bottom right button
    gButtons[3].setPosition(SCREEN_WIDTH - BUTTON_WIDTH, SCREEN_HEIGHT - BUTTON_HEIGHT);

    // Primary loop
    while (isRunning) {
        // Event loop
        while (SDL_PollEvent(&ev) != 0) {
            // Quit button detection
            if (ev.type == SDL_QUIT) {
                isRunning = false;
            }

            for (int i = 0; i < TOTAL_BUTTONS; ++i) {
                gButtons[i].handleEvent(&ev);
            }
        }
        // Clear screen and draw background color
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);

        // Render Buttons
        for (int i = 0; i < TOTAL_BUTTONS; ++i) {
            gButtons[i].render();
        }

        // Update screen
        SDL_RenderPresent(gRenderer);
    }

    clean();

    return 0;
}
