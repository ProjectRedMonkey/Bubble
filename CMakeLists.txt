cmake_minimum_required(VERSION 3.13)
project(Bubble)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lmingw32")
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

set(CMAKE_CXX_STANDARD 14)

find_package(sdl REQUIRED)

add_executable(Bubble main.cpp personages/ennemy.cpp personages/ennemy.h personages/bubble.cpp personages/bubble.h personages/bulle.cpp personages/bulle.h menus/game_over.cpp menus/game_over.h)

target_include_directories(Bubble PUBLIC ${SDL_INCLUDE_DIRS})
target_link_libraries(Bubble ${SDL_LIBRARIES} -lmingw32 -lSDLmain -lSDL -lSDL_mixer -mwindows)