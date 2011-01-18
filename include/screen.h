#ifndef SCREEN_H
#define SCREEN_H

class Engine;

class Screen
{
public:
  virtual ~Screen() {};

  virtual void init(Engine* engine) = 0;

  virtual void handle_input() = 0;

  virtual void update(float delta) = 0;

  virtual void display(float delta, float interpolation) = 0;
};

#endif
