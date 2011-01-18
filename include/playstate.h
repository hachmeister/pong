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

  void speed(float speed);

  void angle(float angle);

  int paddle1;

  int paddle2;

  float ball_pos_x;

  float ball_pos_y;

  float ball_speed_x;

  float ball_speed_y;

private:
  void compute();

  bool has_changed_;

  float ball_speed_;

  float ball_angle_;

};

#endif
