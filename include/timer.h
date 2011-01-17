#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

class Timer
{
  public:
    Timer();

    ~Timer();

    float delta();

  private:
    uint64_t nanos();

    uint64_t start_;
};

#endif
