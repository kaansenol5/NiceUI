#include "Menu.hpp"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_rect.h>

Menu::Menu(const int& Width, const int& Height)
: Width(Width), Height(Height){

}




void Menu::update(){
    for(auto button : buttons){
        button.render();
    }
    for(auto text : texts){
        text.render();
    }
    handle_events();
}

SDL_Rect Menu::set_loc(item_location location, char* text, unsigned char ptsize){
    int x,y,w,h;
    int len = strlen(text);
    w = len * ptsize;
    h = ptsize * 2;

    switch (location) {
        case CENTERED:
            x = (Width/2) - w / 2;
            y = (Height/2) - h / 2;
            break;
        case LEFT:
            x = 0;
            y = (Height/2) - h / 2;
            break;
        case RIGHT:
            x = Width - w;
            y = (Height/2) - h / 2;
            break;
        case DOWN:
            x = (Width/2) - w / 2;
            y = Height - h;
            break;
        case UP:
            x = (Width/2) - w / 2;;
            y = 0;
            break;
    }

    for(auto button : buttons){
        if(button.location.y == y){
                y += button.location.h;
            }
        }
    for(auto text : texts){
        if(text.location.y == y){
             y += text.location.h;
        }
    }
    return {x, y, w, h};
}

void Menu::add_button(char* fontdir, char* text, int ptsize, item_location location,  const std::function<void()> fn){
    SDL_Rect dst_rect = set_loc(location, text, ptsize);
    buttons.push_back({fontdir, text, ptsize, dst_rect, fn});
}

void Menu::add_text(char* fontdir, char* text, int ptsize, item_location location,  SDL_Color color){
    SDL_Rect dst_rect = set_loc(location, text, ptsize);
    texts.push_back({fontdir, text, ptsize, color, dst_rect});
}

void Menu::handle_events(){
    SDL_PumpEvents();
    int x, y;
    Uint32 mouse_state = SDL_GetMouseState(&x, &y);
    for(auto& button : buttons){
        if(x > button.location.x && x < button.location.x + button.location.w && y > button.location.y && y < button.location.y + button.location.h){
            button.selected = true;
            if(mouse_state & SDL_BUTTON(SDL_BUTTON_LEFT)){
                button.on_click(); 
            }
        }
        else {
            button.selected = false;
        }
        
    }
}
