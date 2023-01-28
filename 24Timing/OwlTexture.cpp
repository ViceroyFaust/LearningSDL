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
   
    // Return success if mTexture is populated
    mTexture = newTexture;
    return mTexture;
}

#if defined(SDL_TTF_MAJOR_VERSION)
bool OwlTexture::loadFromRenderedText(std::string text, SDL_Color color) {
    // Get rid of preexisting texture
    free();

    // Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Blended(gFont, text.c_str(), color);
    if (!textSurface) {
        std::cout << "Unable to render text surface: " << TTF_GetError() << "\n";
        return false;
    }
    // Create texture from surface
    mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
    if (!mTexture) {
        std::cout << "Unable to create texture from rendered text: " << SDL_GetError() << "\n";
        SDL_FreeSurface(textSurface);
        return false;
    }
    mWidth = textSurface->w;
    mHeight = textSurface->h;

    SDL_FreeSurface(textSurface);

    // Return success if mTexture is populated
    return mTexture;
}
#endif

void OwlTexture::free() {
    if(mTexture) {
        SDL_DestroyTexture(mTexture);
        mTexture = nullptr;
        mWidth = 0;
        mHeight = 0;
    }
}

void OwlTexture::setColor(Uint8 red, Uint8 green, Uint8 blue) {
    SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void OwlTexture::setBlendMode(SDL_BlendMode blending) {
    SDL_SetTextureBlendMode(mTexture, blending);
}

void OwlTexture::setAlpha(Uint8 alpha) {
    SDL_SetTextureAlphaMod(mTexture, alpha);
}

void OwlTexture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) {
    // Sets the rendering space via rectangle
    SDL_Rect renderRectangle = {x, y, mWidth, mHeight};

    // Set clip rendering dimensions, if clip is not null
    if (clip) {
        renderRectangle.w = clip->w;
        renderRectangle.h = clip->h;
    }
    
    // Render to screen
    SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderRectangle, angle, center, flip);
}

int OwlTexture::getWidth() {
    return mWidth;
}

int OwlTexture::getHeight() {
    return mHeight;
}
