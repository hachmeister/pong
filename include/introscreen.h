#ifndef INTROSCREEN_H
#define INTROSCREEN_H

#include <SDL.h>

#include "screen.h"

class IntroScreen : public Screen
{
public:
  IntroScreen();

  ~IntroScreen();

  void init(Engine* engine);

  void handle_input();

  void update(float delta);

  void display(float delta, float interpolation);

private:
  Engine* engine_;

  SDL_Surface* screen_;

  SDL_Surface* title_;
};

#endif
