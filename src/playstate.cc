#include "playstate.h"

#include <iostream>

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
  }

  float temp_delta = delta;
  while (temp_delta > 0.0f) {
    temp_delta = update_ball_pos(temp_delta);
  }
}

void PlayState::speed(float speed)
{
  ball_speed_ = speed;
  has_changed_ = true;
}

void PlayState::angle(float angle)
{
  while (angle < 0.0f) {
    angle += 360.0f;
  }

  while (angle >= 360.0f) {
    angle -= 360.0f;
  }

  ball_angle_ = angle;
  has_changed_ = true;
}

// private methods

void PlayState::compute()
{
  ball_speed_x = cos(ball_angle_ * PI / 180.0f) * ball_speed_;
  ball_speed_y = sin(ball_angle_ * PI / 180.0f) * ball_speed_;

  has_changed_ = false;
}

float PlayState::update_ball_pos(float delta)
{
  float delta_for_update = delta;
  bool collision = false;

  float new_ball_pos_x = ball_pos_x + (ball_speed_x * delta);
  float new_ball_pos_y = ball_pos_y + (ball_speed_y * delta);

  float delta_x = fabs(new_ball_pos_x - ball_pos_x);
  float delta_y = fabs(new_ball_pos_y - ball_pos_y);
  float new_angle = 0.0f;

  /*
  std::cout << "old x: " << ball_pos_x << "; old y: " << ball_pos_y << "\n";
  std::cout << "new x: " << new_ball_pos_x << "; new y: " << new_ball_pos_y << "\n";
  std::cout << "delta_x: " << fabs(new_ball_pos_x - ball_pos_x) << "; delta_y: " << fabs(new_ball_pos_y - ball_pos_y) << "\n";
  std::cout << "delta2_x: " << (312.0f - fabs(ball_pos_x)) << "; delta2_y: " << (224.0f - fabs(ball_pos_y)) << "\n";
  */

  if (ball_pos_x >= -312.0f && new_ball_pos_x < -312.0f && delta_x > 0.0f) {
    delta_for_update = delta * (312.0f - fabs(ball_pos_x)) / delta_x;
    new_angle = 180.0f - ball_angle_;
    collision = true;
  } else if (ball_pos_x <= 312.0f && new_ball_pos_x > 312.0f && delta_x > 0.0f) {
    delta_for_update = delta * (312.0f - fabs(ball_pos_x)) / delta_x;
    new_angle = 180.0f - ball_angle_;
    collision = true;
  } else if (ball_pos_y >= -224.0f && new_ball_pos_y < -224.0f && delta_y > 0.0f) {
    delta_for_update = delta * (224.0f - fabs(ball_pos_y)) / delta_y;
    new_angle = 360.0f - ball_angle_;
    collision = true;
  } else if (ball_pos_y <= 224.0f && new_ball_pos_y > 224.0f && delta_y > 0.0f) {
    delta_for_update = delta * (224.0f - fabs(ball_pos_y)) / delta_y;
    new_angle = 360.0f - ball_angle_;
    collision = true;
  }

  //std::cout << "delta_for_update: " << delta_for_update << "\n";

  ball_pos_x += ball_speed_x * delta_for_update;
  ball_pos_y += ball_speed_y * delta_for_update;

  //std::cout << "old angle: " << ball_angle_ << "\n";

  if (collision) {
    angle(new_angle);
    compute();
  }

  //std::cout << "new angle: " << ball_angle_ << "\n";

  return delta - delta_for_update;
}
