#include "engine.h"
#include "introscreen.h"

int main()
{
  Engine engine;
  engine.next_state(new IntroScreen());
  engine.start();
}
