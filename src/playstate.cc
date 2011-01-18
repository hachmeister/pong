#include "playstate.h"

#include <cmath>

#define PI 3.14159265

PlayState::PlayState()
  : paddle1(0),
    paddle2(0),
    ball_pos_x(0.0),
    ball_pos_y(0.0),
    ball_speed_x(0.0),
    ball_speed_y(0.0),
    has_changed_(false),
    ball_speed_(0.0),
    ball_angle_(0.0)
{
}

PlayState::PlayState(const PlayState& state)
  : paddle1(state.paddle1),
    paddle2(state.paddle2),
    ball_pos_x(state.ball_pos_x),
    ball_pos_y(state.ball_pos_y),
    ball_speed_x(state.ball_speed_x),
    ball_speed_y(state.ball_speed_y),
    has_changed_(state.has_changed_),
    ball_speed_(state.ball_speed_),
    ball_angle_(state.ball_angle_)
{
}

PlayState::~PlayState()
{
}

void PlayState::update(float delta)
{
  if (has_changed_) {
    compute();
    has_changed_ = false;
  }

  ball_pos_x += ball_speed_x * delta;
  ball_pos_y += ball_speed_y * delta;
}

void PlayState::speed(float speed)
{
  ball_speed_ = speed;
  has_changed_ = true;
}

void PlayState::angle(float angle)
{
  ball_angle_ = angle;
  has_changed_ = true;
}

void PlayState::compute()
{
  ball_speed_x = cos(ball_angle_ * PI / 180.0f) * ball_speed_;
  ball_speed_y = sin(ball_angle_ * PI / 180.0f) * ball_speed_;
}
