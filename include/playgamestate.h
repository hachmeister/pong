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

  void compute(float dt);

  void display();

private:
  Engine* engine_;

  SDL_Surface* screen_;

  SDL_Surface* playfield_;

  int paddle1_;

  int paddle2_;

  float ball_x_;

  float ball_y_;

  float ball_x_speed_;

  float ball_y_speed_;
};

#endif
