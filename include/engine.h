#ifndef ENGINE_H
#define ENGINE_H

#include <SDL.h>

class Screen;

class Engine
{
public:
  Engine();

  ~Engine();

  void next_state(Screen* screen);

  void start();

  void quit();

  SDL_Surface* get_screen() const;

private:
  bool running_;

  SDL_Surface* screen_;

  Screen* current_;

  Screen* next_;
};

#endif
