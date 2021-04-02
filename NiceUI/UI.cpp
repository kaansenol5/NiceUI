#include "UI.hpp"
#include "TextureManager.hpp"
#include "colors.hpp"
#include <SDL2/SDL_render.h>
#include <iostream>

UI::UI(SDL_Renderer* renderer, const int& width, const int& height)
: renderer(renderer), Width(width), Height(height) {
    TextureManager(renderer, Width, Height);
}

void UI::render(){
    menus[current_menu].update();
    SDL_RenderPresent(renderer);
}

void UI::add_menu(std::function<void(Menu &new_menu)> fn){
    Menu new_menu(Width, Height);
    fn(new_menu);
    menus.push_back(std::move(new_menu));
}


void UI::set_background_image(char *imgdir){
    background_image = TextureManager::load_texture(imgdir);
}

void UI::set_background_color(SDL_Color background_color){
    this->background_color = background_color;
}