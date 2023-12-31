#include "vex.h"
#include "Catapult.h"

using namespace vex;

void Catapult::RetractCatapult() {

  CatapultMotor.spin(forward, 100, percent);
}

void Catapult::LaunchCatapult() {

  CatapultMotor.spin(forward, 100, percent);
}

int stoppingAngle = 50;
int wrappingErrorAngle = 350;
void Catapult::StartCatapultMatchLoading() {

  int launches = 0;
  bool added = false;
  while (launches < 44) {

    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(0,0);
    Controller1.Screen.print(launches);
    Controller1.Screen.setCursor(0,5);
    Controller1.Screen.print(InertialSensor.heading());

    CatapultMotor.spin(forward, 100, percent);

    if (Rotation9.angle() < (stoppingAngle) || Rotation9.angle() > wrappingErrorAngle) {

      added = false;
    }

    if ((Rotation9.angle() > stoppingAngle) && (Rotation9.angle() < wrappingErrorAngle) && (added == false)) {

      added = true;
      launches++;      
    }

    if (launches == 40) {

      Controller1.rumble(". . . .");
    }
  }

  CatapultMotor.stop();
}