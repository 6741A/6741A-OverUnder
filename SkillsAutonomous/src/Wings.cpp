#include "vex.h"
#include "Wings.h"

using namespace vex;

void Wings::ExtendWings()
{

  WingPistonLeft.set(true);
  WingPistonRight.set(true);

}


void Wings::RetractWings()
{

  WingPistonLeft.set(false);
  WingPistonRight.set(false);

}
