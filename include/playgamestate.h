#ifndef PLAYGAMESTATE_H
#define PLAYGAMESTATE_H

#include <SDL.h>

#include "gamestate.h"

class PlayGameState : public GameState
{
public:
  PlayGameState();

  ~PlayGameState();

  void init(Engine* engine);

  void handle_input();

  void compute();

  void display();

private:
  Engine* engine_;

  SDL_Surface* screen_;

  SDL_Surface* playfield_;

  int paddle1_;

  int paddle2_;

  int ball_x_;

  int ball_y_;
};

#endif
