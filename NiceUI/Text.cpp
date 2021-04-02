#include "TextureManager.hpp"
#include "Text.hpp"
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

Text::Text(char* fontdir, char* message, int ptsize, SDL_Color color, SDL_Rect location)
: location(location){
    texture = TextureManager::load_ttf_font(fontdir, message, ptsize, color);
}

Text::~Text(){
  //  SDL_DestroyTexture(texture);
}



void Text::render(){
    TextureManager::render(texture, NULL, &location);
}