#include "util.h"

class Button
{
  util::Spritesheet* ss;
  SDL_Rect rect;

public:
  Button();

  void update();
  void draw();
};