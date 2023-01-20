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
    
    // Modulation component
    Uint8 alpha = 255;

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
                    // Increase alpha
                    case SDLK_w:
                        if (alpha + 32 > 255)
                            alpha = 255;
                        else
                            alpha += 32;
                        break;
                    // Decrease alpha
                    case SDLK_s:
                        if (alpha - 32 < 0)
                            alpha = 0;
                        else
                            alpha -= 32;
                        break;
                }
            }
        }
        // Clear screen and draw background color
        SDL_SetRenderDrawColor(gRenderer, 0x2E, 0x34, 0x40, 0xFF);
        SDL_RenderClear(gRenderer);

        // Render background
        gBackgroundTexture.render(0, 0);

        // Render the fading image
        gFadeTexture.setAlpha(alpha);
        gFadeTexture.render(0, 0);

        // Present the render
        SDL_RenderPresent(gRenderer);
        // Prevent the program from hogging the CPU by slowing down the loop
        SDL_Delay(33);
    }

    clean();

    return 0;
}
