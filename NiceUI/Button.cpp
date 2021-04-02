#include "Button.hpp"
#include "TextureManager.hpp"
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

Button::Button(char* fontdir, char* text, int ptsize, SDL_Rect location, const std::function<void()> fn)
: location(location), fn(fn)
{
    texture = TextureManager::load_ttf_font(fontdir, text, ptsize, normal_outline_color);
    outer_rect = {location.x - 5, location.y - 5, location.w + 10, location.h + 10};
    // normal outline color is also the text color
}



Button::~Button(){
    //SDL_DestroyTexture(texture);
}

void Button::on_click(){
    fn();
}

void Button::render(){
    TextureManager::render(texture, NULL, &location);
    if(selected){
        TextureManager::draw_rect(&outer_rect, false, selected_outline_color);
    }
    else{
        TextureManager::draw_rect(&outer_rect, false, normal_outline_color);
    }
    
}