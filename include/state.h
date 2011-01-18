#ifndef STATE_H
#define STATE_H

class State
{
public:
  virtual ~State() {};

  virtual void update(float delta) = 0;
};

#endif
