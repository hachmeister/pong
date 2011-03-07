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
  SDL_FreeSurface(text_);
}

void IntroScreen::init(Engine* engine)
{
  engine_ = engine;
  screen_ = engine_->get_screen();

  SDL_Surface* temp = IMG_Load("data/images/title.png");
  title_ = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);

  font_ = TTF_OpenFont("data/fonts/verdana.ttf", 32);
  TTF_SetFontOutline(font_, 1);
  SDL_Color white;
  white.r = 255;
  white.g = 255;
  white.b = 255;
  
  text_ = TTF_RenderText_Blended(font_, "Test Text...", white);
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

  for (int i = 0; i < 20; i++) {
    rect.x = 100 + 10 * i;
    rect.y = 50 + 10 * i;

    SDL_BlitSurface(text_, NULL, screen_, &rect);
  }

  SDL_Flip(screen_);
}
