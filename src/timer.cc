#include "timer.h"

#include <ctime>

Timer::Timer()
  : start_(nanos())
{
}

Timer::~Timer()
{
}

float Timer::delta()
{
  uint64_t now = nanos();
  float delta = (now - start_) / 1e9;
  start_ = now;
  return delta;
}

// private methods

uint64_t Timer::nanos()
{
  timespec time;
  if (clock_gettime(CLOCK_REALTIME, &time) != 0) {
    return 0;
  }
  return time.tv_sec * 1e9 + time.tv_nsec;
}
