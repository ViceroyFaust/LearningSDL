#ifndef OWLTEXTURE_H
#define OWLTEXTURE_H

#include <SDL.h>
#include <string>

// A wrapper class for SDL Textures
class OwlTexture {
private:
    // The SDL texture backend
    SDL_Texture* mTexture;
    // Image dimensions
    int mWidth;
    int mHeight;

public:
    OwlTexture();
    ~OwlTexture();

    bool loadFromFile(std::string path);

    void free();

    // Set color modulation
    void setColor(Uint8 red, Uint8 green, Uint8 blue);

    // Set blending
    void setBlendMode(SDL_BlendMode blending);

    // Set alpha modulation
    void setAlpha(Uint8 alpha);

    // Render texture at given point w/ optional clipping
    void render(int x, int y, SDL_Rect* clip = nullptr);

    int getWidth();
    int getHeight();
};

#endif
