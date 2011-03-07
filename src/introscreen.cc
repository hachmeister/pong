#include "introscreen.h"

#include <iostream>

#include <SDL_image.h>

#include "engine.h"
#include "playscreen.h"

IntroScreen::IntroScreen()
  : engine_(0),
    renderer_(0),
    font_border_(1)
{
}

IntroScreen::~IntroScreen()
{
  //SDL_FreeSurface(title_);
}

void IntroScreen::init(Engine* engine)
{
  engine_ = engine;
  renderer_ = engine_->get_renderer();

  SDL_Surface* title = IMG_Load("data/images/wow.png");
  title_ = SDL_CreateTextureFromSurface(renderer_, title);
  SDL_FreeSurface(title);
  
  SDL_Color white = {0xFF, 0xFF, 0xFF};
  SDL_Color black = {0x00, 0x00, 0x00};

  int sizes[] = {10, 12, 14, 16, 20, 24, 32, 48, 96};
  char text[] = "World of Warcraft";

  for (unsigned int i = 0; i < sizeof(sizes) / sizeof(sizes[0]); ++i) {
    int size = sizes[i];

    font_ = TTF_OpenFont("data/fonts/Delicious-Bold.ttf", size);
    SDL_Surface* fg_surface = TTF_RenderText_Blended(font_, text, white);
    TTF_CloseFont(font_);

    font_outline_ = TTF_OpenFont("data/fonts/Delicious-Bold.ttf", size);
    TTF_SetFontOutline(font_outline_, font_border_);
    SDL_Surface* bg_surface = TTF_RenderText_Blended(font_outline_, text, black);
    TTF_CloseFont(font_outline_);
    
    text_.push_back(SDL_CreateTextureFromSurface(renderer_, fg_surface));
    outline_.push_back(SDL_CreateTextureFromSurface(renderer_, bg_surface));
    SDL_FreeSurface(bg_surface);
    SDL_FreeSurface(fg_surface);
  }
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
  rect.w = 800;
  rect.h = 600;

  SDL_RenderCopy(renderer_, title_, NULL, &rect);
  
  Uint32 format;
  int access;
  int w;
  int h;
  int outline_h;
  
  rect.x = 50;
  rect.y = 50;

  for (unsigned int i = 0; i < text_.size(); ++i) {
    SDL_Texture* text = text_[i];
    SDL_Texture* outline = outline_[i];
    
    SDL_QueryTexture(outline, &format, &access, &w, &h);
    outline_h = h;

    rect.w = w;
    rect.h = h;
  
    SDL_RenderCopy(renderer_, outline, NULL, &rect);
    
    SDL_QueryTexture(text, &format, &access, &w, &h);

    rect.x += font_border_;
    rect.y += font_border_;
    rect.w = w;
    rect.h = h;

    SDL_RenderCopy(renderer_, text, NULL, &rect);
    
    rect.x -= font_border_;
    rect.y -= font_border_;

    rect.y += outline_h;
  }
  
  SDL_RenderPresent(renderer_);
}
