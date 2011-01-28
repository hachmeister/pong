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

  // computer paddle
  if (ball_speed_x > 0.0f) {
    float delta_move = ((ball_pos_y + 300.0f) - (paddle2 + 300.0f)) * 7.0f * pow((ball_pos_x + 400.0f) / 1200.0f, 2.5f);
    if (delta_move > 20) {
      delta_move = 25;
    }
    else if (delta_move < -20) {
      delta_move = -25;
    }
    paddle2 += delta_move;
  }
  else {
    paddle2 += (300.0f - (paddle2 + 300.0f)) * pow(400.0f / 1200.0f, 3.0f);
  }

  if (paddle2 < -200.0f) {
    paddle2 = -200.0f;
  } else if (paddle2 > 200.0f) {
    paddle2 = 200.0f;
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

float PlayState::speed()
{
  return ball_speed_;
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

float PlayState::angle()
{
  return ball_angle_;
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

  if (ball_pos_x >= -312.0f && new_ball_pos_x < -312.0f && delta_x > 0.0f) {
    float temp_delta_for_update = delta * (312.0f - fabs(ball_pos_x)) / delta_x;

    if (temp_delta_for_update < delta_for_update) {
      float temp_ball_pos_y = ball_pos_y + (ball_speed_y * temp_delta_for_update);
      float ball_distance = fabs(fabs(paddle1 + 400.0f) - fabs(temp_ball_pos_y + 400.0f));

      if (ball_distance < 40.0f) {
        delta_for_update = temp_delta_for_update;
        new_angle = 180.0f - ball_angle_;

        if (ball_pos_y < paddle1) {
          new_angle -= 0.8f * ball_distance;
        }
        else if (ball_pos_y > paddle1) {
          new_angle += 0.8f * ball_distance;
        }

        if (new_angle < -60.0f) {
          new_angle = -60.0f;
        }
        else if (new_angle > 60.0f) {
          new_angle = 60.0f;
        }

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

        if (ball_pos_y < paddle2) {
          new_angle += 0.8f * ball_distance;
        }
        else if (ball_pos_y > paddle2) {
          new_angle -= 0.8f * ball_distance;
        }

        if (new_angle > -120.0f && new_angle < 0.0f) {
          new_angle = -120.0f;
        }
        else if (new_angle > 0.0f && new_angle < 120.0f) {
          new_angle = 120.0f;
        }

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

  ball_pos_x += ball_speed_x * delta_for_update;
  ball_pos_y += ball_speed_y * delta_for_update;

  if (collision) {
    angle(new_angle);
    compute();
  }

  return delta - delta_for_update;
}
