#include "engine.h"

#include <iostream>

#include "gamestate.h"

Engine::Engine()
  : running_(false),
    current_(0),
    next_(0)
{
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    std::cout << "Unable to initialize SDL: " << SDL_GetError() << "\n";
    return;
  }

  screen_ = SDL_SetVideoMode(800, 600, 0, SDL_HWSURFACE | SDL_DOUBLEBUF);

  if (screen_ == NULL) {
    std::cout << "Unable to set video mode: " << SDL_GetError() << "\n";
    return;
  }

  SDL_WM_SetCaption("Pong", NULL);
}

Engine::~Engine()
{
  if (current_) {
    delete current_;
  }

  SDL_Quit();
}

void Engine::next_state(GameState* state)
{
  if (next_) {
    delete next_;
  }

  next_ = state;
}

void Engine::start()
{
  running_ = true;

  while (running_) {
    if (next_) {
      std::cout << "has next\n";
      if (current_) {
        delete current_;
        std::cout << "deleting current\n";
      }
      current_ = next_;
      current_->init(this);
      next_ = 0;
    }

    current_->handle_input();
    current_->display();
  }
}

void Engine::quit()
{
  running_ = false;
}

SDL_Surface* Engine::get_screen() const
{
  return screen_;
}
