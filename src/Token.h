#include "util.h"

#include <SDL2/SDL.h>

class Token
{
  util::Spritesheet* spriteSheet;
  int state;
  SDL_Rect rect;

public:
  Token(util::Spritesheet* spriteSheet, int x, int y);

  void draw();
  SDL_Rect& getRect();
  void setState(int state);
  int getState();

};