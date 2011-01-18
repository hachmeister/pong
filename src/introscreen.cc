#include "introscreen.h"

#include <iostream>

#include <SDL_image.h>

#include "engine.h"
#include "playscreen.h"

IntroScreen::IntroScreen()
  : engine_(0),
    screen_(0)
{
}

IntroScreen::~IntroScreen()
{
  SDL_FreeSurface(title_);
}

void IntroScreen::init(Engine* engine)
{
  engine_ = engine;
  screen_ = engine_->get_screen();

  SDL_Surface* title = IMG_Load("data/images/title.png");
  title_ = SDL_DisplayFormat(title);
  SDL_FreeSurface(title);
}

void IntroScreen::handle_input()
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
            engine_->next_state(new PlayScreen());
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

void IntroScreen::update(float delta)
{
}

void IntroScreen::display(float delta, float interpolation)
{
  SDL_Rect rect;
  rect.x = 0;
  rect.y = 0;

  SDL_BlitSurface(title_, NULL, screen_, &rect);

  SDL_Flip(screen_);
}
