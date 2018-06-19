#include "Token.h"

#include "util.h"

Token::Token(util::Spritesheet* spriteSheet, int x, int y)
{
  state = 0;
  this->spriteSheet = spriteSheet;

  rect = spriteSheet->surface->clip_rect;
  rect.w /= spriteSheet->columns;
  rect.x = util::sdl_screen->w / 2 - rect.w / 2;
  rect.y = util::sdl_screen->h / 2 - rect.h / 2;

  if(x == 0) rect.x -= 166;
  if(x == 2) rect.x += 166;
  if(y == 0) rect.y -= 166;
  if(y == 2) rect.y += 166;
}

void Token::draw()
{
  if(!state)
  {
    if(util::sdl_intersects(util::sdl_mousex(), util::sdl_mousey(), rect))
    {
      util::SpritesheetBlit(spriteSheet, 2, 0, util::sdl_screen, rect.x, rect.y);
    }

    return;
  }

  util::SpritesheetBlit(spriteSheet, state - 1, 0, util::sdl_screen, rect.x, rect.y);
}

SDL_Rect& Token::getRect()
{
  return rect;
}

void Token::setState(int state)
{
  this->state = state;
}

int Token::getState()
{
  return state;
}