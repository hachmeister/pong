#ifndef PLAYSCREEN_H
#define PLAYSCREEN_H

#include <SDL.h>

#include "playstate.h"
#include "screen.h"

class PlayScreen : public Screen
{
public:
  PlayScreen();

  ~PlayScreen();

  void init(Engine* engine);

  void handle_input();

  void update(float delta);

  void display(float delta, float interpolation);

private:
  Engine* engine_;
  
  SDL_Window* window_;

  SDL_Renderer* renderer_;

  SDL_Texture* playfield_;

  PlayState state_;

  float time;
};

#endif
