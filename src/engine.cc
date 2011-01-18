#include "engine.h"

#include <iostream>

#include "screen.h"
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

  running_ = true;
}

Engine::~Engine()
{
  if (current_) {
    delete current_;
  }

  SDL_Quit();
}

void Engine::next_state(Screen* screen)
{
  if (next_) {
    delete next_;
  }

  next_ = screen;
}

void Engine::start()
{
  const uint32_t GAME_SPEED = 25;
  const uint32_t UPDATE_INTERVAL = 1000 / GAME_SPEED;

  Timer timer;
  uint32_t next_update = timer.millis();
  float interpolation = 0.0;

  int frame_count = 0;
  uint32_t frame_count_millis = timer.millis();

  while (running_) {
    if (next_) {
      if (current_) {
        delete current_;
      }
      current_ = next_;
      current_->init(this);
      next_ = 0;
    }

    // handle input
    current_->handle_input();

    // update the state
    while (timer.millis() >= next_update) {
      current_->update(UPDATE_INTERVAL / 1000.0);
      next_update += UPDATE_INTERVAL;
    }

    // display
    interpolation = float(timer.millis() + UPDATE_INTERVAL - next_update) / float(UPDATE_INTERVAL);
    current_->display(UPDATE_INTERVAL / 1000.0, interpolation);

    // fps
    frame_count++;
    if (timer.millis() >= frame_count_millis + 5000) {
      std::cout << "FPS: " << (frame_count / 5) << "\n";
      frame_count_millis = timer.millis();
      frame_count = 0;
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
