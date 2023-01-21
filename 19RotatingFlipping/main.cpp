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
            if (ev.type == SDL_KEYDOWN) {
                switch (ev.key.keysym.sym) {
                    case SDLK_a:
                        degrees -= 15;
                        break;
                    case SDLK_d:
                        degrees += 15;
                        break;
                    case SDLK_q:
                        flipType = SDL_FLIP_HORIZONTAL;
                        break;
                    case SDLK_w:
                        flipType = SDL_FLIP_NONE;
                        break;
                    case SDLK_e:
                        flipType = SDL_FLIP_VERTICAL;

                }
            }
        }
        // Clear screen and draw background color
        SDL_SetRenderDrawColor(gRenderer, 0x2E, 0x34, 0x40, 0xFF);
        SDL_RenderClear(gRenderer);
        
        // render the face in the center
        int screenCenterX = (SCREEN_WIDTH - gFaceTexture.getWidth()) / 2;
        int screenCenterY = (SCREEN_HEIGHT - gFaceTexture.getHeight()) / 2;
        gFaceTexture.render(screenCenterX, screenCenterY, nullptr, degrees, NULL, flipType);

        // Update screen
        SDL_RenderPresent(gRenderer);
    }

    clean();

    return 0;
}
