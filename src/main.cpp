#include "util.h"   // Code to simplify the use of SDL
#include "Token.h"  // Provides the token object (for the 9 squares)
#include "Button.h" // Provides a very simple button

#include <SDL2/SDL.h>       // Provide the base SDL functionality
#include <SDL2/SDL_image.h> // Provide SDL (PNG) image loading

#include <vector> // Provide the standard C++ container (to hold a list of squares)

SDL_Surface* boardImage;    // The image of the board
SDL_Surface* icon;          // The icon for the application
util::Spritesheet* tokenSs; // The token's spritesheet

Button* button;            // The clickable button
std::vector<Token> tokens; // A list of all 9 tokens
int turn = 1;              // The current players turn 1 or 2 (O's or X's)

void clear_board();  // Wipe the board's tokens (for a fresh game)
void check_winner(); // Analyse the board to see if there is a winner
void next_turn();    // Toggle the next turn

/*
 * A callback function for when the top-right button gets clicked.
 */
void on_buttonclick()
{
  /* Task
   *   Try to pick one of the 9 squares at random that is either empty or
   *   owned by the other player. Then set this square so that it is owned
   *   by the current player. Check if this has caused the current player
   *   to win and then move on to the next player's turn.
   */

  /*
   * Useful variables
   *   turn   - The current player 1 or 2 (O's or X's)
   *   tokens - The current list of tokens (all 9 squares on the board)
   *
   * Useful functions
   *   util::random(min, max)       - Generate a random number between min and max
   *   tokens.at(?).getState()      - The current "owner" of the square
   *   tokens.at(?).setState(owner) - The squares owner
   *   check_winner()               - Run through the code to check the board for a winner
   *   next_turn()                  - Toggle the turn to be the next player
   */

  util::message("I don't currently do anything...");
}

/*
 * Handle all the asset loading here
 */
void on_load()
{
  boardImage = IMG_Load("resources/board.png");
  if(!boardImage) util::error("Failed to load image");

  tokenSs = util::SpritesheetLoad("resources/token.png", 3, 1);
  if(!tokenSs) util::error("Failed to load image");

  icon = IMG_Load("resources/icon.png");
  if(!icon) util::error("Failed to load icon");

  for(size_t y = 0; y < 3; y++)
  {
    for(size_t x = 0; x < 3; x++)
    {
      tokens.push_back(Token(tokenSs, x, y));
    }
  }

  button = new Button();
}

/*
 * Handle the game logic per frame here
 */
void on_update()
{
  button->update();

  if(util::sdl_mouseclicked())
  {
    for(auto it = tokens.begin(); it != tokens.end(); it++)
    {
      if(util::sdl_intersects(util::sdl_mousex(), util::sdl_mousey(), it->getRect()) && it->getState() == 0)
      {
        it->setState(turn);
        check_winner();
        next_turn();
      }
    }
  }
}

/*
 * Draw the current game state here
 */
void on_draw()
{
  util::sdl_clearscreen(254, 222, 0);

  util::sdl_blit(boardImage, util::sdl_screen,
    util::sdl_screen->w / 2 - boardImage->w / 2,
    util::sdl_screen->h / 2 - boardImage->h / 2);

  for(auto it = tokens.begin(); it != tokens.end(); it++)
  {
    it->draw();
  }

  button->draw();

  SDL_UpdateWindowSurface(util::sdl_window);
}

/*
 * Free up the native C resources here
 */
void on_cleanup()
{
  util::SpritesheetFree(tokenSs);
  SDL_FreeSurface(boardImage);
  SDL_FreeSurface(icon);
  delete button; // Can be avoided by using RAII
}

/*
 * The main entry point of the application. The program starts here.
 */
int main(int argc, char* args[])
{
  util::sdl_initialize("Introduction Game (C++/SDL)", 800, 600);

  on_load();
  SDL_SetWindowIcon(util::sdl_window, icon);

  while(!util::should_exit)
  {
    util::sdl_poll();
    on_update();
    on_draw();
    SDL_Delay(1000 / 40); // Run at around 40 FPS
  }

  on_cleanup();

  return 0;
}

void next_turn()
{
  turn++;
  if(turn > 2) turn = 1;
}

void check_winner()
{
  auto t = tokens.begin();
  int won = 0;

  for(size_t i = 1; i < 3; i++)
  {
    for(size_t r = 0; r < 3; r++)
    {
      if((t + (r * 3) + 0)->getState() == i &&
        (t + (r * 3) + 1)->getState() == i &&
        (t + (r * 3) + 2)->getState() == i)
      {
        won = i;
        break;
      }
    }

    for(size_t c = 0; c < 3; c++)
    {
      if((t + (0 * 3) + c)->getState() == i &&
        (t + (1 * 3) + c)->getState() == i &&
        (t + (2 * 3) + c)->getState() == i)
      {
        won = i;
        break;
      }
    }

    if((t + 0)->getState() == i &&
      (t + 4)->getState() == i &&
      (t + 8)->getState() == i)
    {
      won = i;
      break;
    }

    if((t + 2)->getState() == i &&
      (t + 4)->getState() == i &&
      (t + 6)->getState() == i)
    {
      won = i;
      break;
    }
  }

  if(won)
  {
    //std::cout << "Winner: " << won << std::endl;
    on_draw();

    if(won == 1)
    {
      util::message("O's Won!");
    }
    else
    {
      util::message("X's Won!");
    }

    clear_board();
    return;
  }

  for(auto it = tokens.begin(); it != tokens.end(); it++)
  {
    if(it->getState() == 0)
    {
      return;
    }
  }

  //std::cout << "Draw" << std::endl;
  on_draw();
  util::message("It was a draw!");
  clear_board();
}

void clear_board()
{
  for(auto it = tokens.begin(); it != tokens.end(); it++)
  {
    it->setState(0);
  }
}