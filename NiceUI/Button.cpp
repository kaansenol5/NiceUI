#include "Button.hpp"
#include "TextureManager.hpp"
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

Button::Button(char* fontdir, char* text, int ptsize, SDL_Rect location, bool filled, const std::function<void(Button& button)> fn)
: location(location), font(fontdir), ptsize(ptsize), text(text), filled(filled), fn(fn)
{
    texture = TextureManager::load_ttf_font(fontdir, text, ptsize, text_color);
    outer_rect = {location.x - 5, location.y - 5, location.w + 10, location.h + 10};
    // normal outline color is also the text color
}



Button::~Button(){
    //SDL_DestroyTexture(texture);
}

void Button::on_click(){
    fn(*this);
}

void Button::change_colors(SDL_Color text_color, SDL_Color normal_outline_color, SDL_Color selected_outline_color){
    this -> text_color = text_color;
    this -> normal_outline_color = normal_outline_color;
    this -> selected_outline_color = selected_outline_color;
    change_text(text); // updates the texture for button text
}

void Button::change_text(char *text){
    SDL_DestroyTexture(texture);
    this -> text = text;
    texture = TextureManager::load_ttf_font(font, text, ptsize, text_color);
}


void Button::render(){
    if(selected){
        TextureManager::draw_rect(&outer_rect, filled, selected_outline_color);
    }
    else{
        TextureManager::draw_rect(&outer_rect, filled, normal_outline_color);
    }
    TextureManager::render(texture, NULL, &location);
}