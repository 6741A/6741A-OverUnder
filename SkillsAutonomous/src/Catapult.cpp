#include "vex.h"
#include "Catapult.h"

using namespace vex;

void Catapult::RetractCatapult()
{

  CatapultMotor.spin(forward, 100, percent);
  
}

void Catapult::LaunchCatapult()
{

  CatapultMotor.spin(forward, 100, percent);

}

void Catapult::StartCatapultMatchLoading()
{

  int launches = 0;

  while (launches < 44)
  {
    RetractCatapult();
    LaunchCatapult();
    launches++;
  }
  
}
