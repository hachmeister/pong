#ifndef INTROGAMESTATE_H
#define INTROGAMESTATE_H

#include <SDL.h>

#include "gamestate.h"

class IntroGameState : public GameState
{
public:
  IntroGameState();

  ~IntroGameState();

  void init(Engine* engine);

  void handle_input();

  void compute(float dt);

  void display();

private:
  Engine* engine_;

  SDL_Surface* screen_;

  SDL_Surface* title_;
};

#endif
