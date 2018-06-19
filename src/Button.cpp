#include "Button.h"

void on_buttonclick();

Button::Button()
{
  ss = util::SpritesheetLoad("resources/button.png", 1, 2);
  if(!ss) util::error("Failed to load button image");

  rect.x = util::sdl_screen->w - ss->surface->w - 10;
  rect.y = 5;
  rect.w = ss->surface->w;
  rect.h = ss->surface->h / ss->rows;
}

void Button::update()
{
  if(util::sdl_intersects(util::sdl_mousex(), util::sdl_mousey(), rect))
  {
    if(util::sdl_mouseclicked())
    {
      on_buttonclick();
    }
  }
}

void Button::draw()
{
  if(util::sdl_intersects(util::sdl_mousex(), util::sdl_mousey(), rect))
  {
    util::SpritesheetBlit(ss, 0, 1, util::sdl_screen, rect.x, rect.y);
  }
  else
  {
    util::SpritesheetBlit(ss, 0, 0, util::sdl_screen, rect.x, rect.y);
  }
}