cmake_minimum_required(VERSION 3.19)


set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -lSDL2 -lSDL2_image -lSDL2_ttf -std=c++17 -pthread -O0")
set(CMAKE_CXX_STANDARD 17)
option(USE_CLANG "build application with clang" ON)
project(nice_ui)

add_executable(
  nice_ui
  test.cpp
  NiceUI/Button.cpp
  NiceUI/Text.cpp
  NiceUI/Menu.cpp
  NiceUI/UI.cpp
  NiceUI/TextureManager.cpp
)
