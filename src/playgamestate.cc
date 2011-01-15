#include "playgamestate.h"

#include <iostream>

#include <SDL_image.h>

#include "engine.h"
#include "introgamestate.h"

PlayGameState::PlayGameState()
  : engine_(0),
    screen_(0),
    paddle1_(0),
    paddle2_(0),
    ball_x_(0),
    ball_y_(0)
{
}

PlayGameState::~PlayGameState()
{
  SDL_FreeSurface(playfield_);
  SDL_WM_GrabInput(SDL_GRAB_OFF);
  SDL_ShowCursor(SDL_ENABLE);
}

void PlayGameState::init(Engine* engine)
{
  engine_ = engine;
  screen_ = engine_->get_screen();

  playfield_ = IMG_Load("data/images/playfield.png");

  SDL_WarpMouse(400, 300);
  SDL_WM_GrabInput(SDL_GRAB_ON);
}

void PlayGameState::handle_input()
{
  SDL_Event event;

  while(SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_KEYDOWN: {
        SDL_KeyboardEvent* key = &event.key;
        switch (key->keysym.sym) {
          case SDLK_ESCAPE:
            engine_->next_state(new IntroGameState());
            break;
          default:
            break;
        }
        break;
      }
      case SDL_MOUSEMOTION: {
        SDL_MouseMotionEvent* motion = &event.motion;
        if (motion->y < 100) {
          paddle1_ = -200;
        } else if (motion->y > 500) {
          paddle1_ = 200;
        } else {
          paddle1_ = motion->y - 300;
        }
        break;
      }
      case SDL_QUIT:
        engine_->quit();
        break;
    }
  }
}

void PlayGameState::compute()
{
  // compute ball and ai player
}

void PlayGameState::display()
{
  SDL_Rect rect;
  rect.x = 0;
  rect.y = 0;

  SDL_BlitSurface(playfield_, NULL, screen_, &rect);

  Uint32 white = SDL_MapRGB(screen_->format, 255, 255, 255);

  SDL_Rect paddle1_rect = {64, 300 - 32 + paddle1_, 16, 64};
  SDL_FillRect(screen_, &paddle1_rect, white);

  SDL_Rect paddle2_rect = {720, 300 - 32 + paddle2_, 16, 64};
  SDL_FillRect(screen_, &paddle2_rect, white);

  SDL_ShowCursor(SDL_DISABLE);
  SDL_Flip(screen_);
}
