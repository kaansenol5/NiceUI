#include "single_include/NiceUI.hpp"


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

    char* fontdir = (char*)"fonts/font.ttf";
    ui.add_menu([fontdir](Menu& menu){
        menu.add_button(fontdir, (char*)"Hello", 24, Menu::CENTERED, true, [](Button& button){
            std::cout << "hello" << std::endl;
            button.change_colors(Colors::Red, Colors::Gray, Colors::White);
        });
        menu.add_button(fontdir, "Quit", 32, Menu::LEFT, false, [](Button& button){
            exit(0);
        });
        menu.add_text(fontdir, "THIS IS A TEST", 21, Menu::UP, Colors::Yellow);
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