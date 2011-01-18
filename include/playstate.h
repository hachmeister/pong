#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include "state.h"

class PlayState : public State
{
public:
  PlayState();

  PlayState(const PlayState& state);

  ~PlayState();

  void update(float delta);

  int paddle1;

  int paddle2;

  float ball_x;

  float ball_y;

  float ball_x_speed;

  float ball_y_speed;
};

#endif
