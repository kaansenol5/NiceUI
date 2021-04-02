#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include "NiceUI/Button.hpp"
#include "NiceUI/UI.hpp"
#include "NiceUI/colors.hpp"
#include <iostream>


/*
THIS IS AN EXAMPLE USAGE
 */


int main(){
    int w = 800;
    int h = 800;

    //SDL INIT
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Hello", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, 0);
    SDL_Renderer* ren = SDL_CreateRenderer(win, 0, SDL_RENDERER_ACCELERATED);
    //SDL INIT
    
    UI ui(ren, w, h); // MAKE AN UI OBJECT

    char* fontdir = (char*)"../fonts/font.ttf";
    std::cout << "aaaa" << std::endl;
    ui.add_menu([fontdir](Menu& menu){
        menu.add_button(fontdir, (char*)"Hello", 24, Menu::CENTERED, [](){
            std::cout << "hello" << std::endl;
        });
    });
    
    for(;;){
        ui.render();
        SDL_Event event;
        SDL_PollEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                return 0;
        }
    }
}