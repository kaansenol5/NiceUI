#include <SDL2/SDL_rect.h>
#pragma once
#include <string>
#include <SDL2/SDL.h>
#include "colors.hpp"
#include <functional>

class Button{
public:
  Button(char* fontdir, char* text, int ptsize, SDL_Rect location, bool filled, const std::function<void(Button& button)> fn);
  ~Button();
  void on_click();
  void render();
  void change_colors(SDL_Color text_color, SDL_Color normal_outline_color, SDL_Color selected_outline_color);
  void change_text(char* text);
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
