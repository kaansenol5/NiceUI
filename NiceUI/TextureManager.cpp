#include "TextureManager.hpp"
#include <SDL2/SDL_render.h>

SDL_Renderer* TextureManager::renderer = nullptr;
int TextureManager::Width = 0;
int TextureManager::Height = 0;