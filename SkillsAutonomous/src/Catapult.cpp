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

    if (Rotation9.position(degrees) > 290)
    {
      Controller1.Screen.clearScreen();
      Controller1.Screen.setCursor(0,0);
      Controller1.Screen.print(launches);
      CatapultMotor.spin(forward, 100, percent);
      waitUntil(!(Rotation9.position(degrees) > 290));
      launches++;
    }

    if (launches == 40)
    {
      Controller1.rumble(". . . .");
    }

  }

  CatapultMotor.stop();
  
}
