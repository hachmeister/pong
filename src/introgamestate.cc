#include "introgamestate.h"

#include <iostream>

#include <SDL_image.h>

#include "engine.h"
#include "playgamestate.h"

IntroGameState::IntroGameState()
  : engine_(0),
    screen_(0)
{
}

IntroGameState::~IntroGameState()
{
  SDL_FreeSurface(title_);
}

void IntroGameState::init(Engine* engine)
{
  engine_ = engine;
  screen_ = engine_->get_screen();

  title_ = IMG_Load("data/images/title.png");
}

void IntroGameState::handle_input()
{
  SDL_Event event;

  while(SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_KEYDOWN: {
        SDL_KeyboardEvent* key = &event.key;
        switch (key->keysym.sym) {
          case SDLK_ESCAPE:
            engine_->quit();
            break;
          case SDLK_SPACE:
            engine_->next_state(new PlayGameState());
          default:
            break;
        }
        break;
      }
      case SDL_QUIT:
        engine_->quit();
        break;
    }
  }
}

void IntroGameState::compute()
{
}

void IntroGameState::display()
{
  SDL_Rect rect;
  rect.x = 0;
  rect.y = 0;

  SDL_BlitSurface(title_, NULL, screen_, &rect);

  SDL_Flip(screen_);
}
