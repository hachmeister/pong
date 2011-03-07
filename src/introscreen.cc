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

  SDL_Surface* title = IMG_Load("data/images/title.png");
  title_ = SDL_DisplayFormat(title);
  SDL_FreeSurface(title);
  
  SDL_Color white = {0xFF, 0xFF, 0xFF};
  SDL_Color black = {0x00, 0x00, 0x00};

  font_ = TTF_OpenFont("data/fonts/Delicious-Roman.ttf", 96);
  //SDL_Surface* fg_surface = TTF_RenderText_Blended(font_, "Pong", white);
  SDL_Surface* fg_surface = TTF_RenderText_Blended(font_, "Hello World!", white);
  SDL_SaveBMP(fg_surface, "foreground.bmp");

  font_outline_ = TTF_OpenFont("data/fonts/Delicious-Roman.ttf", 96);
  TTF_SetFontOutline(font_outline_, 2);
  //SDL_Surface* bg_surface = TTF_RenderText_Blended(font_outline_, "Pong", black);
  SDL_Surface* bg_surface = TTF_RenderText_Blended(font_outline_, "Hello World!", black);
  SDL_SaveBMP(bg_surface, "background.bmp");

  SDL_Rect rect;
  rect.x = 2;
  rect.y = 2;
  rect.w = fg_surface->w;
  rect.h = fg_surface->h;
  SDL_BlitSurface(fg_surface, NULL, bg_surface, &rect);
  SDL_FreeSurface(fg_surface);

  text_ = SDL_DisplayFormatAlpha(bg_surface);
  SDL_SaveBMP(text_, "text.bmp");
  //text_ = SDL_DisplayFormat(bg_surface);
  SDL_FreeSurface(bg_surface);
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
  
  rect.x = 230;
  rect.y = 50;
  rect.w = text_->w;
  rect.h = text_->h;
  
  SDL_BlitSurface(text_, NULL, screen_, &rect);
  
  SDL_Flip(screen_);
}
