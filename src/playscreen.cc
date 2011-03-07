#include "playscreen.h"

#include <iostream>

#include <SDL_image.h>

#include "engine.h"
#include "introscreen.h"

PlayScreen::PlayScreen()
  : engine_(0),
    renderer_(0),
    time(0.0)
{
}

PlayScreen::~PlayScreen()
{
  SDL_SetWindowGrab(window_, SDL_FALSE);
  SDL_ShowCursor(SDL_ENABLE);
}

void PlayScreen::init(Engine* engine)
{
  engine_ = engine;
  window_ = engine_->get_window();
  renderer_ = engine_->get_renderer();

  SDL_Surface* playfield = IMG_Load("data/images/playfield.png");
  playfield_ = SDL_CreateTextureFromSurface(renderer_, playfield);
  SDL_FreeSurface(playfield);

  SDL_WarpMouseInWindow(window_, 400, 300);
  SDL_SetWindowGrab(window_, SDL_TRUE);

  state_.speed(750.0f);
  state_.angle(0.0f);
}

void PlayScreen::handle_input()
{
  SDL_Event event;

  while(SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_KEYDOWN: {
        SDL_KeyboardEvent* key = &event.key;
        switch (key->keysym.sym) {
          case SDLK_ESCAPE:
            engine_->next_state(new IntroScreen());
            break;
          default:
            break;
        }
        break;
      }
      case SDL_MOUSEMOTION: {
        SDL_MouseMotionEvent* motion = &event.motion;
        if (motion->y < 100) {
          state_.paddle1 = -200;
        } else if (motion->y > 500) {
          state_.paddle1 = 200;
        } else {
          state_.paddle1 = motion->y - 300;
        }
        break;
      }
      case SDL_QUIT:
        engine_->quit();
        break;
    }
  }
}

void PlayScreen::update(float delta)
{
  time += delta;
  float new_speed = 750.0f + (50.0f * int(time));
  if (new_speed != state_.speed()) {
    std::cout << "new speed: " << new_speed << "\n";
    state_.speed(new_speed);
  }

  state_.update(delta);
}

void PlayScreen::display(float delta, float interpolation)
{
  // interpolate
  PlayState state(state_);
  state.update(delta * interpolation);

  // draw
  SDL_Rect rect;
  rect.x = 0;
  rect.y = 0;
  rect.w = 800;
  rect.h = 600;

  SDL_RenderCopy(renderer_, playfield_, NULL, &rect);

  SDL_SetRenderDrawColor(renderer_, 255, 255, 255, SDL_ALPHA_OPAQUE);

  // Paddle 1
  SDL_Rect paddle1_rect = {64, 300 - 32 + state.paddle1, 16, 64};
  SDL_RenderFillRect(renderer_, &paddle1_rect);

  // Paddle 2
  SDL_Rect paddle2_rect = {720, 300 - 32 + state.paddle2, 16, 64};
  SDL_RenderFillRect(renderer_, &paddle2_rect);

  // Ball
  SDL_Rect ball_rect = { 400 + state.ball_pos_x - 8, 300 + state.ball_pos_y - 8, 16, 16 };
  SDL_RenderFillRect(renderer_, &ball_rect);

  // Flip screen
  SDL_ShowCursor(SDL_DISABLE);
  SDL_RenderPresent(renderer_);
}
