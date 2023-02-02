#include "constants.h"
#include "globals.h"
#include "util.h"
#include "OwlTimer.h"
#include <SDL.h>
#include <iostream>
#include <sstream> 
#include <iomanip>
#include <queue>

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

    // In memory text stream
    std::stringstream timeText;

    OwlTimer fpsTimer;

    std::queue<Uint32> frameTimeBufferQueue;

    Uint32 frameTimeSum = 0;
    double averageFPS = 0;
   
    int frameCount = 0;
    // Primary loop
    while (isRunning) {
        fpsTimer.start();
        // Event loop
        while (SDL_PollEvent(&ev) != 0) {
            // Quit button detection
            if (ev.type == SDL_QUIT) {
                isRunning = false;
            }
        }

        timeText.str("");
        timeText << "Average Frames Per Second: " << averageFPS;

        if (frameCount >= 10) {
            if (!gFPSTextTexture.loadFromRenderedText(timeText.str().c_str(), textColor)) {
                std::cout << "Failed to render the average FPS texture!\n";
            }
        }

        // Clear screen and draw background color
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);

        // Render the text textures 
        gFPSTextTexture.render((SCREEN_WIDTH - gFPSTextTexture.getWidth()) / 2, 
                (SCREEN_HEIGHT - gFPSTextTexture.getHeight()) / 2);

        // Update screen
        SDL_RenderPresent(gRenderer);
        ++frameCount;
        
        frameTimeBufferQueue.push(fpsTimer.getTicks());
        fpsTimer.stop();

        frameTimeSum += frameTimeBufferQueue.back();

        if (frameTimeBufferQueue.size() == 100) {
            if (frameCount >= 10)
                averageFPS = 100000.0 / frameTimeSum;

            frameTimeSum -= frameTimeBufferQueue.front();
            frameTimeBufferQueue.pop();
        }

        if (frameCount > 10)
            frameCount = 0;
    }

    clean();

    return 0;
}
