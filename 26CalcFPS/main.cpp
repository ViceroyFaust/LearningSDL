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

    OwlTimer fpsTimer;

    // In memory text stream
    std::stringstream timeText;

    // Start counting frames per second
    int countedFrames = 0;
    fpsTimer.start();

    // Primary loop
    while (isRunning) {
        // Event loop
        while (SDL_PollEvent(&ev) != 0) {
            // Quit button detection
            if (ev.type == SDL_QUIT) {
                isRunning = false;
            }
        }

        // Calculate and correct FPS
        double averageFPS = countedFrames / (fpsTimer.getTicks() / 1000.0);
        if (averageFPS > 2000000)
            averageFPS = 0;

        timeText.str("");
        timeText << "Average Frames Per Second: " << averageFPS;

        if (!gFPSTextTexture.loadFromRenderedText(timeText.str().c_str(), textColor)) {
            std::cout << "Failed to render the average FPS texture!\n";
        }
        // Clear screen and draw background color
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);

        // Render the text textures
        gFPSTextTexture.render((SCREEN_WIDTH - gFPSTextTexture.getWidth()) / 2, 
                (SCREEN_HEIGHT - gFPSTextTexture.getHeight()) / 2);

        // Update screen
        SDL_RenderPresent(gRenderer);
        ++countedFrames;
    }

    clean();

    return 0;
}
