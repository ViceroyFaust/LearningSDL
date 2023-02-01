#include "constants.h"
#include "globals.h"
#include "util.h"
#include "OwlTimer.h"
#include <SDL.h>
#include <iostream>
#include <sstream> 
#include <iomanip>

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

    // Black text color
    SDL_Color textColor = {0, 0, 0, 255};

    OwlTimer timer;

    // In memory text stream
    std::stringstream timeText;

    // Primary loop
    while (isRunning) {
        // Event loop
        while (SDL_PollEvent(&ev) != 0) {
            // Quit button detection
            if (ev.type == SDL_QUIT) {
                isRunning = false;
            } else if (ev.type == SDL_KEYDOWN) {
                switch (ev.key.keysym.sym) {
                    case SDLK_s:
                        if (timer.isStarted())
                            timer.stop();
                        else
                            timer.start();
                        break;
                    case SDLK_p:
                        if (timer.isPaused())
                            timer.unpause();
                        else
                            timer.pause();
                }
            }
        }

        timeText.str("");
        timeText << "Seconds since start time: " << (timer.getTicks() / 1000.0);

        if (!gTimeTextTexture.loadFromRenderedText(timeText.str().c_str(), textColor)) {
            std::cout << "Failed to render the time texture!\n";
        }
        // Clear screen and draw background color
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);

        // Render the text textures
        gPromptTexture.render((SCREEN_WIDTH - gPromptTexture.getWidth()) / 2, 0);
        gTimeTextTexture.render((SCREEN_WIDTH - gTimeTextTexture.getWidth()) / 2, 
                (SCREEN_HEIGHT - gTimeTextTexture.getHeight()) / 2);

        // Update screen
        SDL_RenderPresent(gRenderer);
    }

    clean();

    return 0;
}
