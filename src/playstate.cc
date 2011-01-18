#include "playstate.h"

PlayState::PlayState()
  : paddle1(0),
    paddle2(0),
    ball_x(0.0),
    ball_y(0.0),
    ball_x_speed(0.0),
    ball_y_speed(0.0)
{
}

PlayState::PlayState(const PlayState& state)
  : paddle1(state.paddle1),
    paddle2(state.paddle2),
    ball_x(state.ball_x),
    ball_y(state.ball_y),
    ball_x_speed(state.ball_x_speed),
    ball_y_speed(state.ball_y_speed)
{
}

PlayState::~PlayState()
{
}

void PlayState::update(float delta)
{
  ball_x += ball_x_speed * delta;
  ball_y += ball_y_speed * delta;
}
