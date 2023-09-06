/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:                                                                 */
/*    Created:      Sat Sep 2 2023                                            */
/*    Description:  6741A Skills Challenge program                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/


#include "vex.h"
#include "PositionTracker.h"
#include "Robot.h"

using namespace vex;

// A global instance of competition
competition Competition;
// text
void pre_auton(void) 
{
  
  vexcodeInit();

}

// Instantiate Mover class object
Robot robot;

void autonomous(void) 
{


}

void DriverControls()
{

  LeftMotors.spin(forward, (Controller1.Axis3.value() + Controller1.Axis1.value() * 2), percent);
  RightMotors.spin(forward, (Controller1.Axis3.value() - Controller1.Axis1.value() * 2), percent);

}


void usercontrol(void) 
{

  while (1) 
  {

    DriverControls();

    wait(20, msec);

  }

}

int main() 
{

  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) 
  {
    wait(100, msec);
  }
  
}
