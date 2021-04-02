#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include "SDL2/SDL_ttf.h"
#include "Menu.hpp"
#include <functional>
#include <string>
#include <vector>



class UI{
public:
  UI(SDL_Renderer* renderer, const int& width, const int& height);
  void render();
  void set_background_image(char* imgdir);
  void set_background_color(SDL_Color background_color);
  void add_menu(std::function<void(Menu &new_menu)> fn);
  int current_menu = 0;
private:
  std::vector<Menu> menus; // menus[0] is main menu
  SDL_Renderer* renderer;
  const int& Width;
  const int& Height;
  SDL_Texture* background_image;
  SDL_Color background_color = {158,158,158,100}; // defaults to semi transparent gray to print a layer on top of background_image

};

