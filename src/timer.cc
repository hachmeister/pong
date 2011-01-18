#include "timer.h"

#include <ctime>

Timer::Timer()
  : start_(nanos())
{
}

Timer::~Timer()
{
}

uint32_t Timer::millis()
{
  uint64_t now = nanos();
  uint32_t millis = (now - start_) / 1e6;
  return millis;
}

// private methods

uint64_t Timer::nanos()
{
  timespec ts;
  if (clock_gettime(CLOCK_MONOTONIC, &ts) != 0) {
    return 0;
  }
  return ts.tv_sec * 1e9 + ts.tv_nsec;
}
