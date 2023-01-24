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
            } else if (ev.type == SDL_KEYDOWN) {
                switch (ev.key.keysym.sym) {
                    case SDLK_1:
                        Mix_PlayChannel(-1, gWilhelm, 0);
                        break;
                    case SDLK_2:
                        Mix_PlayChannel(-1, gMinecraftOof, 0);
                        break;
                    case SDLK_3:
                        Mix_PlayChannel(-1, gMinecraftCave, 0);
                        break;
                    case SDLK_4:
                        Mix_PlayChannel(01, gRobloxOof, 0);
                        break;
                    case SDLK_9:
                        // If no music is playing
                        if (Mix_PlayingMusic() == 0) {
                            Mix_PlayMusic(gMusic, -1);
                        } else if (Mix_PausedMusic() == 1) { // If music is paused
                            Mix_ResumeMusic();
                        } else {
                            Mix_PauseMusic();
                        }
                        break;
                    case SDLK_0:
                        Mix_HaltMusic();
                }
            }

        }
        // Clear screen and draw background color
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);

        gBackgroundTexture.render(0, 0);

        // Update screen
        SDL_RenderPresent(gRenderer);
    }

    clean();

    return 0;
}
