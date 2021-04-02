#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>


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

