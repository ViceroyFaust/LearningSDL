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

    // Render texture at given point w/ optional clipping
    void render(int x, int y, SDL_Rect* clip = nullptr);

    int getWidth();
    int getHeight();
};

#endif
