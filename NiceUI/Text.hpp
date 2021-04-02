#pragma once
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <string>

class Text{
public:
    Text(char* fontdir, char* message, int ptsize, SDL_Color color, SDL_Rect location);
    ~Text();
    void render();
    SDL_Rect location;
private:
    SDL_Texture* texture;
};