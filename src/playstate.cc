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
  //std::cout << "--------\n";

  float delta_for_update = delta;
  bool collision = false;

  float new_ball_pos_x = ball_pos_x + (ball_speed_x * delta);
  float new_ball_pos_y = ball_pos_y + (ball_speed_y * delta);

  float delta_x = fabs(new_ball_pos_x - ball_pos_x);
  float delta_y = fabs(new_ball_pos_y - ball_pos_y);
  float new_angle = 0.0f;

  /*
  std::cout << "old x: " << ball_pos_x << "; old y: " << ball_pos_y << "\n";
  std::cout << "temp x: " << new_ball_pos_x << "; temp y: " << new_ball_pos_y << "\n";
  std::cout << "delta_x: " << fabs(new_ball_pos_x - ball_pos_x) << "; delta_y: " << fabs(new_ball_pos_y - ball_pos_y) << "\n";
  std::cout << "delta2_x: " << (312.0f - fabs(ball_pos_x)) << "; delta2_y: " << (224.0f - fabs(ball_pos_y)) << "\n";
  */

  if (ball_pos_x >= -312.0f && new_ball_pos_x < -312.0f && delta_x > 0.0f) {
    float temp_delta_for_update = delta * (312.0f - fabs(ball_pos_x)) / delta_x;
    if (temp_delta_for_update < delta_for_update) {
      float temp_ball_pos_y = ball_pos_y + (ball_speed_y * temp_delta_for_update);
      float ball_distance = fabs(fabs(paddle1 + 400.0f) - fabs(temp_ball_pos_y + 400.0f));
      /*
      std::cout << "    ball: " << ball_pos_y << " + (" << ball_speed_y << " * " << temp_delta_for_update << ") = " << temp_ball_pos_y << " (" << int(temp_ball_pos_y) << ")\n";
      std::cout << "  paddle: " << paddle1 << " (" << int(paddle1) << ")\n";
      std::cout << "distance: " << ball_distance << "\n";
      */
      if (ball_distance < 40.0f) {
        delta_for_update = temp_delta_for_update;
        new_angle = 180.0f - ball_angle_;
        collision = true;
      }
    }
  }
  if (ball_pos_x <= 312.0f && new_ball_pos_x > 312.0f && delta_x > 0.0f) {
    float temp_delta_for_update = delta * (312.0f - fabs(ball_pos_x)) / delta_x;
    if (temp_delta_for_update < delta_for_update) {
      float temp_ball_pos_y = ball_pos_y + (ball_speed_y * temp_delta_for_update);
      float ball_distance = fabs(fabs(paddle2 + 400.0f) - fabs(temp_ball_pos_y + 400.0f));
      if (ball_distance < 40.0f) {
        delta_for_update = temp_delta_for_update;
        new_angle = 180.0f - ball_angle_;
        collision = true;
      }
    }
  }
  if (ball_pos_y >= -224.0f && new_ball_pos_y < -224.0f && delta_y > 0.0f) {
    float temp_delta_for_update = delta * (224.0f - fabs(ball_pos_y)) / delta_y;
    if (temp_delta_for_update < delta_for_update) {
      delta_for_update = temp_delta_for_update;
      new_angle = 360.0f - ball_angle_;
      collision = true;
    }
  }
  if (ball_pos_y <= 224.0f && new_ball_pos_y > 224.0f && delta_y > 0.0f) {
    float temp_delta_for_update = delta * (224.0f - fabs(ball_pos_y)) / delta_y;
    if (temp_delta_for_update < delta_for_update) {
      delta_for_update = temp_delta_for_update;
      new_angle = 360.0f - ball_angle_;
      collision = true;
    }
  }

  //std::cout << "delta_for_update: " << delta_for_update << "\n";

  ball_pos_x += ball_speed_x * delta_for_update;
  ball_pos_y += ball_speed_y * delta_for_update;

  //std::cout << "new x: " << ball_pos_x << "; new y: " << ball_pos_y << "\n";

  if (collision) {
    angle(new_angle);
    compute();
  }

  // computer paddle
  paddle2 += ((ball_pos_y + 300.0f) - (paddle2 + 300.0f)) * pow((ball_pos_x + 400.0f) / 1200.0f, 2.5f);

  return delta - delta_for_update;
}
