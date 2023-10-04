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
  bool added = false;

  while (launches < 43)
  {
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(0,0);
    Controller1.Screen.print(launches);

    CatapultMotor.spin(forward, 100, percent);

    if (Rotation9.angle() < 59 || Rotation9.angle() > 350)
    {
      added = false;
    }

    if ((Rotation9.angle() > 62) && (Rotation9.angle() < 350) && (added == false))
    {

      added = true;
      launches++;
      //waitUntil(!(Rotation9.angle() > 62));
      
    }

    if (launches == 40)
    {
      Controller1.rumble(". . . .");
    }

  }

  CatapultMotor.stop();
  
}



