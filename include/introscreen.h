#ifndef INTROSCREEN_H
#define INTROSCREEN_H

#include <SDL.h>
#include <SDL_ttf.h>

#include <vector>

#include "screen.h"

class IntroScreen : public Screen
{
public:
  IntroScreen();

  ~IntroScreen();

  void init(Engine* engine);

  void handle_input();

  void update(float delta);

  void display(float delta, float interpolation);

private:
  Engine* engine_;

  SDL_Renderer* renderer_;

  SDL_Texture* title_;
  
  TTF_Font* font_;
  
  TTF_Font* font_outline_;
  
  int font_border_;

  std::vector<SDL_Texture*> text_;
  std::vector<SDL_Texture*> outline_;
};

#endif
