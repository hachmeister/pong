#include "engine.h"
#include "introgamestate.h"

int main()
{
  Engine engine;
  engine.next_state(new IntroGameState());
  engine.start();
}
