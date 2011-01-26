#include "playscreen.h"

#include <iostream>

#include <SDL_image.h>

#include "engine.h"
#include "introscreen.h"

PlayScreen::PlayScreen()
  : engine_(0),
    screen_(0)
{
}

PlayScreen::~PlayScreen()
{
  SDL_FreeSurface(playfield_);
  SDL_WM_GrabInput(SDL_GRAB_OFF);
  SDL_ShowCursor(SDL_ENABLE);
}

void PlayScreen::init(Engine* engine)
{
  engine_ = engine;
  screen_ = engine_->get_screen();

  SDL_Surface* playfield = IMG_Load("data/images/playfield.png");
  playfield_ = SDL_DisplayFormat(playfield);
  SDL_FreeSurface(playfield);

  SDL_WarpMouse(400, 300);
  SDL_WM_GrabInput(SDL_GRAB_ON);

  state_.speed(500.0f);
  state_.angle(195.0f);
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
        /*
        state_.ball_pos_x = motion->x - 400.0f;
        state_.ball_pos_y = motion->y - 300.0f;
        std::cout << "  ball: " << state_.ball_pos_x << " (" << int(state_.ball_pos_x) << "), " << state_.ball_pos_y << " (" << int(state_.ball_pos_y) << ")\n";
        std::cout << "paddle: " << state_.paddle1 << " (" << int(state_.paddle1) << ")\n";
        */
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
  state_.update(delta);

  /*
  if (state_.ball_pos_y < -224.0f) {
    engine_->quit();
  }
  */
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

  SDL_BlitSurface(playfield_, NULL, screen_, &rect);

  Uint32 white = SDL_MapRGB(screen_->format, 255, 255, 255);

  // Paddle 1
  SDL_Rect paddle1_rect = {64, 300 - 32 + state.paddle1, 16, 64};
  SDL_FillRect(screen_, &paddle1_rect, white);

  // Paddle 2
  SDL_Rect paddle2_rect = {720, 300 - 32 + state.paddle2, 16, 64};
  SDL_FillRect(screen_, &paddle2_rect, white);

  // Ball
  SDL_Rect ball_rect = { 400 + state.ball_pos_x - 8, 300 + state.ball_pos_y - 8, 16, 16 };
  SDL_FillRect(screen_, &ball_rect, white);

  // Flip screen
  SDL_ShowCursor(SDL_DISABLE);
  SDL_Flip(screen_);
}
