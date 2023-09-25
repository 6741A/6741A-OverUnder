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
    CatapultMotor.spin(forward, 100, percent);
    if (CataLimit)
    {
      launches++;
      wait(0.2, msec);
    }
  }
  
}
