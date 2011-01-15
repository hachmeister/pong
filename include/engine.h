#ifndef ENGINE_H
#define ENGINE_H

#include <SDL.h>

class GameState;

class Engine
{
public:
  Engine();

  ~Engine();

  void next_state(GameState* state);

  void start();

  void quit();

  SDL_Surface* get_screen() const;

private:
  bool running_;

  SDL_Surface* screen_;

  GameState* current_;

  GameState* next_;
};

#endif
