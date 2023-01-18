#include "OwlTexture.h"
#include "globals.h"

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>


OwlTexture::OwlTexture() : mTexture{nullptr}, mWidth{0}, mHeight{0}
{}

OwlTexture::~OwlTexture() {
    free();
}

bool OwlTexture::loadFromFile(std::string path) {
    // Get rid of the previous texture
    free();
    // Final texture, to return
    SDL_Texture* newTexture = nullptr;
    // Load image from path to surface
    SDL_Surface* loadedImage = IMG_Load(path.c_str());
    if (!loadedImage) {
        std::cout << "Failed to load image " << path << ": " << SDL_GetError() << "\n";
        return false;
    }
    // Magenta color key
    SDL_SetColorKey(loadedImage, SDL_TRUE, SDL_MapRGB(loadedImage->format, 0xFF, 0x00, 0xFF));
   
    // Create a texture from surface
    newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedImage);
    if (!newTexture) {
        std::cout << "Surface to Texture Conversion Error,"
            << path << ": " << SDL_GetError() << "\n";
        // Free memory for the unused loadedImage
        SDL_FreeSurface(loadedImage);
        return false;
    }
    mWidth = loadedImage->w;
    mHeight = loadedImage->h;
    // Free memory for unused loadedImage
    SDL_FreeSurface(loadedImage);
    
    mTexture = newTexture;
    return mTexture;
}

void OwlTexture::free() {
    if(mTexture) {
        SDL_DestroyTexture(mTexture);
        mTexture = nullptr;
        mWidth = 0;
        mHeight = 0;
    }
}

void OwlTexture::render(int x, int y) {
    // Sets the rendering space via rectangle
    SDL_Rect renderRectangle = {x, y, mWidth, mHeight};
    SDL_RenderCopy(gRenderer, mTexture, NULL, &renderRectangle);
}

int OwlTexture::getWidth() {
    return mWidth;
}

int OwlTexture::getHeight() {
    return mHeight;
}
