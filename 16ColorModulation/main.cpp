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
    
    // Modulation components
    Uint8 r = 255;
    Uint8 g = 255;
    Uint8 b = 255;

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
                    // Increase red
                    case SDLK_q:
                        r += 32;
                        break;
                    // Increase green
                    case SDLK_w:
                        g += 32;
                        break;
                    // Increase blue
                    case SDLK_e:
                        b += 32;
                        break;
                    // Decrease red
                    case SDLK_a:
                        r -= 32;
                        break;
                    // Decrease green
                    case SDLK_s:
                        g -= 32;
                        break;
                    // Decrease blue
                    case SDLK_d:
                        b -= 32;
                }
            }
        }
        // Clear screen and draw background color
        SDL_SetRenderDrawColor(gRenderer, 0x2E, 0x34, 0x40, 0xFF);
        SDL_RenderClear(gRenderer);
        // Modulate and render the texture
        gPhoto.setColor(r, g, b);
        gPhoto.render(0, 0);

        // Present the render
        SDL_RenderPresent(gRenderer);
        // Prevent the program from hogging the CPU by slowing down the loop
        SDL_Delay(33);
    }

    clean();

    return 0;
}
