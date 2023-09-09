#include "vex.h"
#include "Wings.h"

using namespace vex;

void Wings::ExtendWings()
{

  WingPistonLeft = true;
  WingPistonRight = true;

}


void Wings::RetractWings()
{

  WingPistonLeft = false;
  WingPistonRight = false;

}
