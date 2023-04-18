#include <SDL2/SDL_rect.h>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_pixels.h>
#include <vector>
#include <SDL2/SDL_render.h>
#include <functional>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <iostream>
//COLORS.HPP
namespace NiceUI{
namespace Colors{
  const SDL_Color White = {255,255,255,255};
  const SDL_Color Red = {255,0,0,255};
  const SDL_Color Green = {0,255,0,255};
  const SDL_Color Blue = {0,0,255,255};
  const SDL_Color Gray = {158,158,158,255};
  const SDL_Color Yellow = {246,255,0,255};
  const SDL_Color Black = {0,0,0,0};
};
//COLORS.HPP END
//TEXTUREMANAGER.HPP

class TextureManager{
public:
    inline TextureManager(SDL_Renderer* ren, int w, int h){
        TTF_Init();
        IMG_Init(IMG_INIT_PNG);
        renderer = ren;
        Width = w;
        Height = h;
    }

    static inline SDL_Texture* load_texture(std::string dir){
        SDL_Surface* temp = IMG_Load(dir.c_str());
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, temp);
        SDL_FreeSurface(temp);
        return texture;
  }

  static inline SDL_Texture* load_ttf_font(char* font_dir, char* message, int ptsize, SDL_Color color){
    TTF_Font* font = TTF_OpenFont(font_dir, ptsize);
    if (font == nullptr){
      std::cout << "loaded font might not exist, segfault incoming" << std::endl;
    }
    SDL_Surface* temp_surface = TTF_RenderText_Solid(font, message, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, temp_surface);
    SDL_FreeSurface(temp_surface);
    TTF_CloseFont(font);
    return texture;

  }

  static inline bool check_bounds(SDL_Rect *dest){
    if(dest->x > -100 && dest->x < Width+100 && dest->y > -100 && dest->y < Height+100){
      return true;
    }
    else{
      return false;
    }
  }

  static inline void render(SDL_Texture* texture, SDL_Rect *source, SDL_Rect *dest){
    if(check_bounds(dest)){ //check if destination rect is in the screen
      if(SDL_RenderCopy(renderer, texture, source, dest) != 0){
        std::cout << SDL_GetError() << dest->x << " "  << dest->y << std::endl;
      }
    }
  }

  static inline void draw_rect(SDL_Rect *dest, bool filled, SDL_Color color){
    if(check_bounds(dest)){
      SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
      if(filled){
        SDL_RenderFillRect(renderer, dest);
      }
      else{
        SDL_RenderDrawRect(renderer, dest);
      }
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    }
  }
private:
    static SDL_Renderer* renderer;
    static int Width; 
    static int Height;
};
SDL_Renderer* TextureManager::renderer = nullptr;
int TextureManager::Width = 0;
int TextureManager::Height = 0;
//TEXTUREMANAGER.HPP END
//BUTTON.HPP
class Button{
public:
  inline Button(char* fontdir, char* text, int ptsize, SDL_Rect location, bool filled, const std::function<void(Button& button)> fn):
   location(location), font(fontdir), ptsize(ptsize), text(text), filled(filled), fn(fn)
{
    texture = TextureManager::load_ttf_font(fontdir, text, ptsize, text_color);
    outer_rect = {location.x - 5, location.y - 5, location.w + 10, location.h + 10};
    // normal outline color is also the text color
}
  inline ~Button(){
    //SDL_DestroyTexture(texture);
}
  inline void on_click(){
    fn(*this);
}
  inline void render(){
    if(selected){
        TextureManager::draw_rect(&outer_rect, filled, selected_outline_color);
    }
    else{
        TextureManager::draw_rect(&outer_rect, filled, normal_outline_color);
    }
    TextureManager::render(texture, NULL, &location);
}
  inline void change_colors(SDL_Color text_color, SDL_Color normal_outline_color, SDL_Color selected_outline_color){
    this -> text_color = text_color;
    this -> normal_outline_color = normal_outline_color;
    this -> selected_outline_color = selected_outline_color;
    change_text(text); // updates the texture for button text
}
  inline void change_text(char* text){
    SDL_DestroyTexture(texture);
    this -> text = text;
    texture = TextureManager::load_ttf_font(font, text, ptsize, text_color);
}
  SDL_Rect location;
  bool selected = false;
  char* text;
  SDL_Color text_color = Colors::White;
  SDL_Color normal_outline_color = Colors::Black;
  SDL_Color selected_outline_color = Colors::Red;
private:
  char* font;
  int ptsize;
  bool filled;
  SDL_Rect outer_rect;
  SDL_Texture* texture;
  const std::function<void(Button& button)> fn;
};
//BUTTON.HPP END
//TEXT.HPP
class Text{
public:
    inline Text(char* fontdir, char* message, int ptsize, SDL_Color color, SDL_Rect location): 
    location(location){
    texture = TextureManager::load_ttf_font(fontdir, message, ptsize, color);
}
    inline ~Text(){
  //  SDL_DestroyTexture(texture);
}

    inline void render(){
    TextureManager::render(texture, NULL, &location);
}
    SDL_Rect location;
private:
    SDL_Texture* texture;
};
//TEXT.HPP END
//MENU.HPP
class Menu{
public:
  inline Menu(const int& Width, const int& Height): 
  Width(Width), Height(Height){

  } 


  enum item_location{
    CENTERED, LEFT, RIGHT, DOWN, UP
  };
  inline void update(){
    for(auto button : buttons){
        button.render();
    }
    for(auto text : texts){
        text.render();
    }
    handle_events();
}

  inline void add_button(char* fontdir, char* text, int ptsize, item_location location, bool filled, const std::function<void(Button& button)> fn){
    SDL_Rect dst_rect = set_loc(location, text, ptsize);
    buttons.push_back({fontdir, text, ptsize, dst_rect, filled, fn});
}
  inline void add_text(char* fontdir, char* text, int ptsize, item_location location,  SDL_Color color){
    SDL_Rect dst_rect = set_loc(location, text, ptsize);
    texts.push_back({fontdir, text, ptsize, color, dst_rect});
}
private:
  inline SDL_Rect set_loc(item_location location, char* text, unsigned char ptsize){
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
        if(button.location.y == y && button.location.x == x){
                y += button.location.h;
            }
        }
    for(auto text : texts){
        if(text.location.y == y && text.location.x == x){
             y += text.location.h;
        }
    }
    return {x, y, w, h};
}
  const int& Width; // screen dimensions
  const int& Height; // ^^^^^^^^^^^^^^^
  inline void handle_events(){
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

  std::vector<Button> buttons;
  std::vector<Text> texts;
};
//MENU.HPP END


//UI.hpp
class UI{
public:
  inline UI(SDL_Renderer* renderer, const int& width, const int& height): renderer(renderer), Width(width), Height(height) {
    TextureManager(renderer, Width, Height);
}
  inline void render(){
    menus[current_menu].update();
    SDL_RenderPresent(renderer);
}
  inline void set_background_image(char* imgdir){
    background_image = TextureManager::load_texture(imgdir);
}
  inline void set_background_color(SDL_Color background_color){
    this->background_color = background_color;
}
  inline void add_menu(std::function<void(Menu &new_menu)> fn){
    Menu new_menu(Width, Height);
    fn(new_menu);
    menus.push_back(std::move(new_menu));
}

  int current_menu = 0;
private:
  std::vector<Menu> menus; // menus[0] is main menu
  SDL_Renderer* renderer;
  const int& Width;
  const int& Height;
  SDL_Texture* background_image;
  SDL_Color background_color = {158,158,158,100}; // defaults to semi transparent gray to print a layer on top of background_image

};
//UI.hpp END
}