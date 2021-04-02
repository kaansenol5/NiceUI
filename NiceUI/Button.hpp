#include <SDL2/SDL_rect.h>
#pragma once
#include <string>
#include <SDL2/SDL.h>
#include "colors.hpp"
#include <functional>

class Button{
public:
  Button(char* fontdir, char* text, int ptsize, SDL_Rect location, const std::function<void()> fn);
  ~Button();
  void on_click();
  void render();
  SDL_Rect location;
  bool selected = false;
private:
  SDL_Rect outer_rect;
  SDL_Texture* texture;
  SDL_Color normal_outline_color = Colors::Gray;
  SDL_Color selected_outline_color = Colors::White;
  const std::function<void()> fn;
};
