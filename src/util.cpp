#include "util.h"

#ifdef _WIN32
  #include <windows.h>
#endif

#include <SDL2/SDL_image.h>

#include <iostream>

#include <stdlib.h>

namespace util
{

SDL_Window* sdl_window;
SDL_Surface* sdl_screen;
bool should_exit;
double delta_time;
bool mouse_clicked;
int mouse_x;
int mouse_y;

bool sdl_mouseclicked()
{
  if(mouse_clicked)
  {
    mouse_clicked = false;
    return true;
  }

  return false;
}

int sdl_mousex()
{
  return mouse_x;
}

int sdl_mousey()
{
  return mouse_y;
}

void log(std::string message)
{
  std::cout << "[util]" << message << std::endl;
}

void cleanup()
{
  log("Cleaning up SDL2");
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void error(std::string message)
{
  std::cout << "Error: " << message << std::endl;
#ifdef _WIN32
  MessageBox(0, message.c_str(), "Game Error", 0);
#endif
  exit(1);
}

void message(std::string message)
{
  std::cout << "Message: " << message << std::endl;
#ifdef _WIN32
  MessageBox(0, message.c_str(), "Game Message", 0);
#endif
}

void sdl_initialize(std::string title, int width, int height)
{
  log("Initializing SDL2");

  if(SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    error("Failed to initialize SDL");
  }

  sdl_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

  if(!sdl_window)
  {
    error("Failed to open window");
  }

  sdl_screen = SDL_GetWindowSurface(sdl_window);
  atexit(cleanup);
}

void sdl_poll()
{
  static Uint32 now = 0;
  static Uint32 last = 0;

  now = SDL_GetTicks();
  delta_time = (now - last) / 1000.0f;
  last = now;
  mouse_clicked = false;

  SDL_Event e = { 0 };

  while (SDL_PollEvent(&e) != 0)
  {
    if( e.type == SDL_QUIT )
    {
      should_exit = true;
    }
    else if (e.type == SDL_MOUSEBUTTONDOWN)
    {
      mouse_clicked = true;
    }
    else if(e.type == SDL_MOUSEMOTION)
    {
      mouse_x = e.motion.x;
      mouse_y = e.motion.y;
    }
  }
}

void sdl_clearscreen(int r, int g, int b)
{
  SDL_FillRect(sdl_screen, &sdl_screen->clip_rect, SDL_MapRGB(sdl_screen->format, r, g, b));
}

void sdl_blit(SDL_Surface* src, SDL_Surface* dest, int x, int y)
{
  SDL_Rect r = { 0 };
  r.x = x;
  r.y = y;
  SDL_BlitSurface(src, NULL, dest, &r);
}

bool sdl_keydown(SDL_Keycode key)
{
  const Uint8* state = SDL_GetKeyboardState(NULL);

  if (state[(Uint8)key]) return true;
  return false;
}


Spritesheet* SpritesheetLoad(std::string path, int columns, int rows)
{
  Spritesheet* rtn = new Spritesheet();
  rtn->surface = IMG_Load(path.c_str());

  if(!rtn->surface) return NULL;

  rtn->rows = rows;
  rtn->columns = columns;

  return rtn;
}

void SpritesheetFree(Spritesheet* ctx)
{
  SDL_FreeSurface(ctx->surface);
  delete ctx;
}

void SpritesheetBlit(Spritesheet* ctx, int column, int row, SDL_Surface* dest, int x, int y)
{
  SDL_Rect sr = {0};

  column = column % ctx->columns;
  row = row % ctx->rows;

  sr.w = ctx->surface->w / ctx->columns;
  sr.h = ctx->surface->h / ctx->rows;
  sr.x = sr.w * column;
  sr.y = sr.h * row;

  SDL_Rect dr = {0};

  dr.x = x;
  dr.y = y;

  SDL_BlitSurface(ctx->surface, &sr, dest, &dr);
}

bool sdl_intersects(int x, int y, SDL_Rect& rect)
{
  SDL_Rect res = {0};
  SDL_Rect r = {0};
  r.x = x;
  r.y = y;
  r.w = 1;
  r.h = 1;

  if(SDL_IntersectRect(&r, &rect, &res)) return true;

  return false;
}

int random(int min, int max)
{
  return rand() % (max - min + 1) + min;
}

}
