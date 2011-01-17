#include "engine.h"

#include <iostream>

#include "gamestate.h"
#include "timer.h"

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
  const float dt = 0.01;
  
  running_ = true;

  Timer timer;
  float accu = 0.0;
  
  float fi = 0.0;
  int fc = 0;

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

    // add delta time
    float delta = timer.delta();
    accu += delta;
    fi += delta;

    // handle input
    current_->handle_input();

    // update the state
    while (accu >= dt) {
      current_->compute(dt);
      accu -= dt;
    }

    // display
    current_->display();

    // fps
    fc++;
    if (fi >= 5.0) {
      std::cout << "FPS: " << (fc / 5.0) << "\n";
      fi -= 5.0;
      fc = 0;
    }
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
