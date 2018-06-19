#ifndef UTIL_H
#define UTIL_H

#include <SDL2/SDL.h>

#include <string>

namespace util
{

struct Spritesheet
{
  int rows;
  int columns;
  SDL_Surface* surface;
};

extern SDL_Window* sdl_window;
extern SDL_Surface* sdl_screen;
extern bool should_exit;
extern double delta_time;

void sdl_initialize(std::string title, int width, int height);
void sdl_poll();
void sdl_clearscreen(int r, int g, int b);
void sdl_blit(SDL_Surface* src, SDL_Surface* dest, int x, int y);
bool sdl_keydown(SDL_Keycode key);
bool sdl_intersects(int x, int y, SDL_Rect& b);
bool sdl_mouseclicked();
int sdl_mousex();
int sdl_mousey();

Spritesheet* SpritesheetLoad(std::string path, int columns, int rows);
void SpritesheetFree(Spritesheet* ctx);
void SpritesheetBlit(Spritesheet* ctx, int column, int row, SDL_Surface* dest, int x, int y);

void error(std::string message);
void message(std::string message);
int random(int min, int max);

}

#endif
