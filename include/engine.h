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

  SDL_Window* get_window() const;

  SDL_Renderer* get_renderer() const;

private:
  bool running_;

  SDL_Surface* screen_;
  
  SDL_Window* window_;
  
  SDL_Renderer* renderer_;

  Screen* current_;

  Screen* next_;
};

#endif
