#include "Button.hpp"
#include "Text.hpp"
#include <vector>




class Menu{
public:
  Menu(const int& Width, const int& Height);

  enum item_location{
    CENTERED, LEFT, RIGHT, DOWN, UP
  };
  void update();
  void add_button(char* fontdir, char* text, int ptsize, item_location location, bool filled, const std::function<void(Button& button)> fn);
  void add_text(char* fontdir, char* text, int ptsize, item_location location,  SDL_Color color);
private:
  SDL_Rect set_loc(item_location loc, char* text, unsigned char ptsize); 
  const int& Width; // screen dimensions
  const int& Height; // ^^^^^^^^^^^^^^^
  void handle_events();
  std::vector<Button> buttons;
  std::vector<Text> texts;
};