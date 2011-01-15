#ifndef GAMESTATE_H
#define GAMESTATE_H

class Engine;

class GameState
{
public:
  virtual ~GameState() {};

  virtual void init(Engine* engine) = 0;

  virtual void handle_input() = 0;

  virtual void compute() = 0;

  virtual void display() = 0;
};

#endif
